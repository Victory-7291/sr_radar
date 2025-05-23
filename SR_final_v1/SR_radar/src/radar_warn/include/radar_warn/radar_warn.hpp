#ifndef RADAR_WARN_HPP
#define RADAR_WARN_HPP

#include <rclcpp/rclcpp.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <vision_interface/msg/detect_result.hpp>
#include <vision_interface/msg/radar_warn.hpp>
#include <vision_interface/msg/radar2_sentry.hpp>
#include <radar_interface/team_color.hpp>
#include "radar_utils/radar_utils.h"
#include <deque>

namespace tdt_radar {

class RadarWarn : public rclcpp::Node {
public:
    explicit RadarWarn(const rclcpp::NodeOptions& options);
    ~RadarWarn() = default;

private:
    // 回调函数
    void detect_callback(const std::shared_ptr<vision_interface::msg::DetectResult> msg);
    void color_callback(const radar_interface::team_color::msg::SharedPtr msg);
    
    // 计算两点之间的距离
    float calculate_distance(const cv::Point2f& p1, const cv::Point2f& p2);
    
    // 订阅者
    rclcpp::Subscription<vision_interface::msg::DetectResult>::SharedPtr detect_sub_;
    rclcpp::Subscription<radar_interface::team_color::msg>::SharedPtr color_sub_;
    
    // 发布者
    rclcpp::Publisher<vision_interface::msg::RadarWarn>::SharedPtr warn_pub_;
    rclcpp::Publisher<vision_interface::msg::Radar2Sentry>::SharedPtr radar2sentry_pub_;
    
    // 工具类
    std::unique_ptr<parser> parser_;
    
    // 团队颜色
    radar_interface::team_color::ENUM self_color;
    
    // 存储机器人位置
    cv::Point2f blue_point[6];
    cv::Point2f red_point[6];
    
    // 时间戳相关
    double blue_update[6];
    double red_update[6];
    
    // 状态计数器
    int hero_count1;
    int hero_count2;
    
    // 英雄机器人历史位置
    struct HeroPosition {
        cv::Point2f position;
        double timestamp;
    };
    std::deque<HeroPosition> hero_history; // 存储英雄机器人的历史位置
    double hero_history_duration = 2.0; // 历史记录保留时间（秒）
    float min_movement_threshold = 1.0f; // 最小移动阈值（米）
    
    // 预警相关
    int warning_level = 0; // 预警等级：0-不预警，1-可能预警，2-明确预警
    double last_warning_active_time = 0.0; // 最后一次预警激活的时间
    double warning_hold_duration = 1.0; // 预警保持时间（秒）
    double last_hero_detected_time = 0.0; // 最后一次检测到敌方英雄的时间
    double time_since_last_detection =0.0;
    double possible_warning_timeout = 5.0; // 触发可能预警所需的未检测到敌方英雄的时间（秒）
};

}  // namespace tdt_radar

#endif  // RADAR_WARN_HPP