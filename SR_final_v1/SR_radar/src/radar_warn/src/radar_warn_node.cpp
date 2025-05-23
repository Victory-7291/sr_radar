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
    
    color_sub_ = this->create_subscription<radar_interface::team_color::msg>(
        "judge/color", 10, std::bind(&RadarWarn::color_callback, this, std::placeholders::_1));
    
    // 初始化发布者
    warn_pub_ = this->create_publisher<vision_interface::msg::RadarWarn>(
        "/hero_state", 10);
    
    radar2sentry_pub_ = this->create_publisher<vision_interface::msg::Radar2Sentry>(
        "/Radar2Sentry", rclcpp::SensorDataQoS());
    
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
    
    // 初始化最后检测时间
    last_hero_detected_time = 0.0;
    
    RCLCPP_INFO(this->get_logger(), "RadarWarn节点已启动");
}

void RadarWarn::color_callback(const radar_interface::team_color::msg::SharedPtr msg) {
    self_color = msg->data ? radar_interface::team_color::C_RED : radar_interface::team_color::C_BLUE;
    RCLCPP_INFO(this->get_logger(), "团队颜色已接收: %s", 
                self_color == radar_interface::team_color::C_RED ? "红色" : "蓝色");
}

float RadarWarn::calculate_distance(const cv::Point2f& p1, const cv::Point2f& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

void RadarWarn::detect_callback(const std::shared_ptr<vision_interface::msg::DetectResult> msg) {
    // 获取当前时间
    std::cout<<"1111111111111111"<<std::endl;
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
    
    // 计算未检测到敌方英雄的时间
    double time_since_last_detection = current_time - last_hero_detected_time;
    
    // 使用条件语句设置warning_level，不需要先重置为0
    
    // 如果检测到敌方英雄机器人
    if (enemy_hero_detected) {
        // 更新最后检测到敌方英雄的时间
        last_hero_detected_time = current_time;
        
        // 添加当前位置到历史记录
        hero_history.push_back({enemy_hero_position, current_time});
        
        // 移除过时的历史记录，但至少保留两个记录
        while (hero_history.size() > 2 && current_time - hero_history.front().timestamp > hero_history_duration) {
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
                
                // 敌方英雄机器人在指定时间内移动距离小于阈值，发出明确预警（等级2）
                warning_level = 2; // 明确预警
                last_warning_active_time = current_time; // 更新最后一次预警激活时间
                RCLCPP_WARN(this->get_logger(), "敌方英雄机器人预警（等级2）：移动距离 %.2f 米，小于阈值 %.2f 米", 
                           distance_moved, min_movement_threshold);
            } else {
                warning_level = 0; // 不预警
            }
        } else {
            warning_level = 0; // 不预警
        }
    } else {
        // 未检测到敌方英雄机器人
        // 如果之前是明确预警状态，且在保持时间内，则继续保持预警状态
        if (current_time - last_warning_active_time <= warning_hold_duration) {
            warning_level = 2; // 继续保持明确预警
            RCLCPP_INFO(this->get_logger(), "未检测到敌方英雄，但预警状态保持中%.1f", 
                       warning_hold_duration - (current_time - last_warning_active_time));
        } else if(!hero_history.empty() && time_since_last_detection >= possible_warning_timeout){
            // 检查是否应该发出可能预警（等级1）
            // 条件：未检测到敌方英雄达到5秒 且 最后记录的位置y坐标小于22
            // 获取最新的历史记录
            const auto& latest_record = hero_history.back();
            // 如果y坐标小于22，则发出可能预警
            if (latest_record.position.y < 22) {
                warning_level = 1; // 可能预警
                RCLCPP_INFO(this->get_logger(), "敌方英雄机器人可能预警（等级1）：未检测到敌方英雄%.1f秒，最后位置y=%.2f < 22", 
                           time_since_last_detection, latest_record.position.y);
            } else {
                warning_level = 0; // 不预警
            }
        } else {
            warning_level = 0; // 不预警
        }
    }

    RCLCPP_INFO(this->get_logger(), "敌方英雄机器人预警等级1：%d", warning_level);
    
    // 发布预警消息
    vision_interface::msg::RadarWarn radar_warn;
    radar_warn.hero_state = warning_level; // 使用预警等级
    warn_pub_->publish(radar_warn);
    
    // 发布Radar2Sentry消息
    vision_interface::msg::Radar2Sentry radar2sentry;
    
    // 根据团队颜色发送敌方机器人信息
    if (self_color == radar_interface::team_color::C_BLUE) {
        // 我方是蓝色，发送红色机器人信息
        for (int i = 0; i < 6; i++) {
            if (red_point[i].x != 0 && red_point[i].y != 0 && current_time - red_update[i] < 2.0) {
                radar2sentry.radar_enemy_x[i] = red_point[i].x;
                radar2sentry.radar_enemy_y[i] = red_point[i].y;
            }
        }
    } else if (self_color == radar_interface::team_color::C_RED) {
        // 我方是红色，发送蓝色机器人信息
        for (int i = 0; i < 6; i++) {
            if (blue_point[i].x != 0 && blue_point[i].y != 0 && current_time - blue_update[i] < 2.0) {
                radar2sentry.radar_enemy_x[i] = blue_point[i].x;
                radar2sentry.radar_enemy_y[i] = blue_point[i].y;
            }
        }
    }
    
    radar2sentry_pub_->publish(radar2sentry);
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