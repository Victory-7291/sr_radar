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
    void engine_state_callback(const std::shared_ptr<vision_interface::msg::DetectResult> msg);
    
    // 计算两点之间的距离
    float calculate_distance(const cv::Point2f& p1, const cv::Point2f& p2);
    
    // 订阅者
    rclcpp::Subscription<vision_interface::msg::DetectResult>::SharedPtr detect_sub_;
    rclcpp::Subscription<vision_interface::msg::DetectResult>::SharedPtr engine_detect_sub_;
    rclcpp::Subscription<radar_interface::team_color::msg>::SharedPtr color_sub_;
    
    // 发布者
    rclcpp::Publisher<vision_interface::msg::RadarWarn>::SharedPtr warn_pub_;
    rclcpp::Publisher<vision_interface::msg::Radar2Sentry>::SharedPtr radar2sentry_pub_;
    rclcpp::Publisher<vision_interface::msg::RadarWarn>::SharedPtr engine_warn_pub_;
    
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
    
    // 位置历史记录结构体
    struct RobotPositionRecord {
        cv::Point2f position;
        double timestamp;
        bool in_area; // 对于工程机器人，表示是否在中心高地
    };
    
    // 持久化机器人位置所需的结构体
    struct RobotPosition {
        float x = 0.0f;
        float y = 0.0f;
        bool valid = false;
    };
    
    // 存储机器人的最后位置（索引0-1分别对应英雄(0)和工程(1)机器人）
    RobotPosition red_robots_last_position[2];
    RobotPosition blue_robots_last_position[2];
    
    // 英雄机器人历史位置
    std::deque<RobotPositionRecord> hero_history; // 存储英雄机器人的历史位置
    double hero_history_duration = 2.5; // 历史记录保留时间（秒）
    float min_movement_threshold = 0.2f; // 最小移动阈值（米）
    
    // 工程机器人历史位置和状态
    std::deque<RobotPositionRecord> engine_history; // 存储工程机器人的历史位置和状态
    double engine_in_area_duration = 1.0; // 在中心高地持续时间触发预警（秒）
    double engine_out_area_duration = 0.5; // 离开中心高地持续时间解除预警（秒）
    int engine_warning_level = 0; // 工程机器人预警等级：0-不预警，1-预警
    
    // 预警相关
    int warning_level = 0; // 英雄预警等级：0-不预警，1-预警
};

}  // namespace tdt_radar

#endif  // RADAR_WARN_HPP