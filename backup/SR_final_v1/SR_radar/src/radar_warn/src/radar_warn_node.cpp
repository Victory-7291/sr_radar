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
    
    // 初始化预警等级
    warning_level = 0;
    engine_warning_level = 0;
    
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
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    double current_time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() / 1000.0;
    
    // 尝试获取敌方工程机器人位置（索引为1）
    cv::Point2f engine_position;
    bool engine_detected = false;
    
    // 根据团队颜色获取敌方工程机器人位置
    if (self_color == radar_interface::team_color::C_BLUE && msg->red_x[1] && msg->red_y[1]) {
        engine_position = cv::Point2f(msg->red_x[1], msg->red_y[1]);
        engine_detected = true;
    } else if (self_color == radar_interface::team_color::C_RED && msg->blue_x[1] && msg->blue_y[1]) {
        engine_position = cv::Point2f(msg->blue_x[1], msg->blue_y[1]);
        engine_detected = true;
    }
    
    if (engine_detected) {
        // 判断工程机器人是否在中心高地
        bool in_center_highland = parser_->isPointInCenterHighland(engine_position);
        
        // 记录位置和状态
        engine_history.push_back({engine_position, current_time, in_center_highland});
        
        // 移除超过5秒的过时记录，保留至少2条记录
        while (engine_history.size() > 2 && current_time - engine_history.front().timestamp > 5.0) {
            engine_history.pop_front();
        }
        
        // 检查最近1秒内的记录，判断是否全部在中心高地内
        bool continuously_in_highland = true;
        bool continuously_outside_highland = true;
        
        for (const auto& record : engine_history) {
            double time_diff = current_time - record.timestamp;
            
            // 检查是否持续在高地内1秒
            if (time_diff <= engine_in_area_duration && !record.in_area) {
                continuously_in_highland = false;
            }
            
            // 检查是否持续在高地外0.5秒
            if (time_diff <= engine_out_area_duration && record.in_area) {
                continuously_outside_highland = false;
            }
        }
        
        // 根据持续状态更新预警等级
        int prev_warning_level = engine_warning_level;
        
        if (continuously_in_highland && engine_history.size() >= 2) {
            engine_warning_level = 1; // 持续在高地内，触发预警
        } else if (continuously_outside_highland && engine_history.size() >= 2) {
            engine_warning_level = 0; // 持续在高地外，解除预警
        }
        
        // 只在预警状态改变时输出日志
        if (prev_warning_level != engine_warning_level) {
            if (engine_warning_level == 1) {
                RCLCPP_WARN(this->get_logger(), "敌方工程机器人持续在中心高地1秒以上，发出预警");
            } else {
                RCLCPP_INFO(this->get_logger(), "敌方工程机器人已离开中心高地0.5秒以上，解除预警");
            }
        }
        
        RCLCPP_INFO(this->get_logger(), "工程机器人: (%.2f, %.2f), 在高地: %s, 预警: %d", 
                   engine_position.x, engine_position.y, 
                   in_center_highland ? "是" : "否", 
                   engine_warning_level);
    }
    
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
    int prev_warning_level = warning_level;
    warning_level = 0;
    
    // 获取敌方英雄机器人的位置（编号为1，在数组中索引为0）
    cv::Point2f enemy_hero_position;
    bool enemy_hero_detected = false;
    
    if (self_color == radar_interface::team_color::C_BLUE && red_point[0].x != 0 && red_point[0].y != 0) {
        // 我方是蓝色，敌方英雄是红色的第一个机器人
        enemy_hero_position = red_point[0];
        enemy_hero_detected = true;
    } else if (self_color == radar_interface::team_color::C_RED && blue_point[0].x != 0 && blue_point[0].y != 0) {
        // 我方是红色，敌方英雄是蓝色的第一个机器人
        enemy_hero_position = blue_point[0];
        enemy_hero_detected = true;
    }
    
    // 处理敌方英雄机器人预警逻辑
    if (enemy_hero_detected) {
        // 检测到敌方英雄，添加位置到历史记录
        hero_history.push_back({enemy_hero_position, current_time, false}); // in_area对英雄不使用，设为false
        
        // 移除超过hero_history_duration的过时历史记录，但至少保留两个记录
        while (hero_history.size() > 2 && current_time - hero_history.front().timestamp > hero_history_duration+0.5) {
            hero_history.pop_front();
        }
        
        // 如果有足够的历史数据，检查在整个时间窗口内的移动情况
        if (hero_history.size() >= 2) {
            // 计算最大移动距离，检查英雄是否在指定时间内基本静止
            float max_movement = 0.0f;
            bool has_significant_movement = false;
            
            // 计算当前位置与所有hero_history_duration内的历史位置的距离
            for (const auto& record : hero_history) {
                // 只检查在hero_history_duration时间窗口内的记录
                if (current_time - record.timestamp <= hero_history_duration) {
                    float distance = calculate_distance(enemy_hero_position, record.position);
                    
                    // 如果有任何一个距离超过阈值，认为有显著移动
                    if (distance >= min_movement_threshold) {
                        has_significant_movement = true;
                        max_movement = std::max(max_movement, distance);
                        // 不需要再检查其他记录
                        break;
                    }
                    
                    max_movement = std::max(max_movement, distance);
                }
            }
            
            // 英雄在整个时间窗口内的移动距离都小于阈值，发出预警
            if (!has_significant_movement && hero_history.size() >= 3 && 
                current_time - hero_history.front().timestamp >= hero_history_duration) {
                warning_level = 1;
                if (prev_warning_level != warning_level) {
                    RCLCPP_WARN(this->get_logger(), "敌方英雄机器人预警：在%.1f秒内最大移动距离为%.2f米，小于阈值%.2f米", 
                               hero_history_duration, max_movement, min_movement_threshold);
                }
            } else {
                warning_level = 0;
                if (prev_warning_level != warning_level && has_significant_movement) {
                    RCLCPP_INFO(this->get_logger(), "敌方英雄机器人正常移动：在%.1f秒内最大移动距离为%.2f米，大于阈值%.2f米",
                               hero_history_duration, max_movement, min_movement_threshold);
                }
            }
            
            RCLCPP_INFO(this->get_logger(), "英雄机器人: (%.2f, %.2f), 最大移动: %.2f米, 预警: %d", 
                       enemy_hero_position.x, enemy_hero_position.y, max_movement, warning_level);
        }
    } else {
        // 未检测到敌方英雄机器人，不预警
        warning_level = 0;
    }
    
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