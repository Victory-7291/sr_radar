#include <rclcpp/rclcpp.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <vision_interface/msg/detect_result.hpp>
#include <vision_interface/msg/radar_warn.hpp>
#include <vision_interface/msg/radar2_sentry.hpp>
#include <radar_interface/team_color.hpp>
#include "radar_utils/radar_utils.h"
#include "radar_warn/radar_warn.hpp"

namespace tdt_radar {

RadarWarn::RadarWarn(const rclcpp::NodeOptions& options)
    : Node("radar_warn", options) {
    
    // 初始化订阅者
    detect_sub_ = this->create_subscription<vision_interface::msg::DetectResult>(
        "/kalman_detect", 10, std::bind(&RadarWarn::detect_callback, this, std::placeholders::_1));
    
    // 新增：专门用于工程机器人状态监测的订阅者
    engine_detect_sub_ = this->create_subscription<vision_interface::msg::DetectResult>(
        "/detect_result", rclcpp::SensorDataQoS(), std::bind(&RadarWarn::engine_state_callback, this, std::placeholders::_1));
    
    color_sub_ = this->create_subscription<radar_interface::team_color::msg>(
        "judge/color", rclcpp::SystemDefaultsQoS(), std::bind(&RadarWarn::color_callback, this, std::placeholders::_1));
    
    // 初始化发布者
    warn_pub_ = this->create_publisher<vision_interface::msg::RadarWarn>(
        "/hero_state", rclcpp::SystemDefaultsQoS());
    
    //radar2sentry_pub_ = this->create_publisher<vision_interface::msg::Radar2Sentry>(
    //    "/Radar2Sentry", rclcpp::SensorDataQoS());
    
    engine_warn_pub_ = this->create_publisher<vision_interface::msg::RadarWarn>(
        "/engine_state", rclcpp::SystemDefaultsQoS());
    
    // 初始化parser
    parser_ = std::make_unique<parser>();
    
    // 初始化团队颜色
    self_color = radar_interface::team_color::UNKNOWN;
    
    // 初始化计数器
    hero_count1 = 0;
    hero_count2 = 0;
    
    // 初始化时间戳数组
    for (int i = 0; i < 6; i++) {
        blue_update[i] = 0.0;
        red_update[i] = 0.0;
    }
    
    //RCLCPP_INFO(this->get_logger(), "RadarWarn节点已启动");
}

void RadarWarn::color_callback(const radar_interface::team_color::msg::SharedPtr msg) {
    self_color = msg->data ? radar_interface::team_color::C_RED : radar_interface::team_color::C_BLUE;
    //RCLCPP_INFO(this->get_logger(), "团队颜色已接收: %s", 
    //            self_color == radar_interface::team_color::C_RED ? "红色" : "蓝色");
}

float RadarWarn::calculate_distance(const cv::Point2f& p1, const cv::Point2f& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

void RadarWarn::engine_state_callback(const std::shared_ptr<vision_interface::msg::DetectResult> msg) {
    // 工程机器人检测逻辑（工程机器人编号为2，在数组中索引为1）
    int engine_warning_level = 0;
    cv::Point2f engine_position;
    bool engine_detected = false;


    
    // 只更新工程机器人的位置（索引为1）
    if (self_color == radar_interface::team_color::C_BLUE) {
        // 获取敌方（红色）工程机器人位置
        if (msg->red_x[1] && msg->red_y[1]) {
            // 只更新红方工程机器人位置
            engine_position = cv::Point2f(msg->red_x[1], msg->red_y[1]);
            engine_detected = true;
        }
    } else if (self_color == radar_interface::team_color::C_RED) {
        // 获取敌方（蓝色）工程机器人位置
        if (msg->blue_x[1] && msg->blue_y[1]) {
            // 只更新蓝方工程机器人位置
            engine_position = cv::Point2f(msg->blue_x[1], msg->blue_y[1]);
            engine_detected = true;
        }
    }
    
    if (engine_detected) {
        // 使用isPointInCenterHighland判断工程机器人是否在中心高地
        if (parser_->isPointInCenterHighland(engine_position)) {
            engine_warning_level = 1;
            RCLCPP_WARN(this->get_logger(), "敌方工程机器人位于中心高地，发出预警");
        } else {
            engine_warning_level = 0;
            RCLCPP_INFO(this->get_logger(), "敌方工程机器人不在中心高地");
        }
    } 
    //else {
    //    RCLCPP_INFO(this->get_logger(), "未检测到敌方工程机器人");
    //}
    
    // 发布工程机器人预警消息
    vision_interface::msg::RadarWarn engine_warn;
    engine_warn.engine_state = engine_warning_level;
    engine_warn_pub_->publish(engine_warn);
}

void RadarWarn::detect_callback(const std::shared_ptr<vision_interface::msg::DetectResult> msg) {
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    double current_time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() / 1000.0;
    
    // 更新机器人位置数据
    for (int i = 0; i < 6; i++) {
        if (msg->blue_x[i] && msg->blue_y[i]) {
            blue_point[i] = cv::Point2f(msg->blue_x[i], msg->blue_y[i]);
            blue_update[i] = current_time;
        }
        if (msg->red_x[i] && msg->red_y[i]) {
            red_point[i] = cv::Point2f(msg->red_x[i], msg->red_y[i]);
            red_update[i] = current_time;
        }
    }
    
    // 默认设置预警等级为0（不预警）
    warning_level = 0;
    
    // 获取敌方英雄机器人的位置（编号为1，在数组中索引为0）
    cv::Point2f enemy_hero_position;
    bool enemy_hero_detected = false;
    
    if (self_color == radar_interface::team_color::C_BLUE) {
        // 我方是蓝色，敌方英雄是红色的第一个机器人
        if (red_point[0].x != 0 && red_point[0].y != 0) {
            enemy_hero_position = red_point[0];
            enemy_hero_detected = true;
        }
    } else if (self_color == radar_interface::team_color::C_RED) {
        // 我方是红色，敌方英雄是蓝色的第一个机器人
        if (blue_point[0].x != 0 && blue_point[0].y != 0) {
            enemy_hero_position = blue_point[0];
            enemy_hero_detected = true;
        }
    }
    
    // 处理敌方英雄机器人预警逻辑
    if (enemy_hero_detected) {
        // 检测到敌方英雄，添加位置到历史记录
        hero_history.push_back({enemy_hero_position, current_time});
        
        // 移除超过2秒的过时历史记录，但至少保留两个记录
        while (hero_history.size() > 2 && current_time - hero_history.front().timestamp > hero_history_duration+0.5) {
            hero_history.pop_front();
        }
        
        // 如果有足够的历史数据，检查移动情况
        if (hero_history.size() > 1) {
            // 获取最早的有效历史记录
            const auto& oldest_record = hero_history.front();
            
            // 计算移动距离
            float distance_moved = calculate_distance(enemy_hero_position, oldest_record.position);
            
            // 检查是否需要发出预警
            if (distance_moved < min_movement_threshold && 
                current_time - oldest_record.timestamp >= hero_history_duration) {
                
                // 敌方英雄机器人在指定时间内移动距离小于阈值，发出预警
                warning_level = 1; // 设置为预警状态
                RCLCPP_WARN(this->get_logger(), "敌方英雄机器人预警：移动距离 %.2f 米，小于阈值 %.2f 米", 
                           distance_moved, min_movement_threshold);
            } else {
                // 移动距离大于阈值，不预警
                warning_level = 0;
                RCLCPP_INFO(this->get_logger(), "敌方英雄机器人正常移动：移动距离 %.2f 米，大于阈值 %.2f 米",
                           distance_moved, min_movement_threshold);
            }
        }
    } else {
        // 未检测到敌方英雄机器人，不预警
        warning_level = 0;
        //RCLCPP_INFO(this->get_logger(), "未检测到敌方英雄机器人");
    }
    
    RCLCPP_INFO(this->get_logger(), "敌方英雄机器人预警等级：%d", warning_level);
    
    // 发布预警消息
    vision_interface::msg::RadarWarn radar_warn;
    radar_warn.hero_state = warning_level;
    warn_pub_->publish(radar_warn);
    
    // 发布Radar2Sentry消息
    //vision_interface::msg::Radar2Sentry radar2sentry;
    //
    //// 根据团队颜色发送敌方机器人信息
    //if (self_color == radar_interface::team_color::C_BLUE) {
    //    // 我方是蓝色，发送红色机器人信息
    //    for (int i = 0; i < 6; i++) {
    //        if (red_point[i].x != 0 && red_point[i].y != 0 && current_time - red_update[i] < 2.0) {
    //            radar2sentry.radar_enemy_x[i] = red_point[i].x;
    //            radar2sentry.radar_enemy_y[i] = red_point[i].y;
    //        }
    //    }
    //} else if (self_color == radar_interface::team_color::C_RED) {
    //    // 我方是红色，发送蓝色机器人信息
    //    for (int i = 0; i < 6; i++) {
    //        if (blue_point[i].x != 0 && blue_point[i].y != 0 && current_time - blue_update[i] < 2.0) {
    //            radar2sentry.radar_enemy_x[i] = blue_point[i].x;
    //            radar2sentry.radar_enemy_y[i] = blue_point[i].y;
    //        }
    //    }
    //}
    //
    //radar2sentry_pub_->publish(radar2sentry);
}

}  // namespace tdt_radar

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    auto options = rclcpp::NodeOptions();
    auto node = std::make_shared<tdt_radar::RadarWarn>(options);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}