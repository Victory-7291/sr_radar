#pragma once

#include <queue>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <std_msgs/msg/u_int16.hpp>
#include <std_msgs/msg/bool.hpp>
#include <radar_interface/msg/radar_info.hpp>


class DvTriggerNode : public rclcpp::Node
{
private:
    struct dv_context_t {
        uint8_t now_chances;
        bool is_dv_trigered;
        uint8_t used_chances;
        unsigned waiting_for_check; // 不为 0 时表示等待确认易伤，每检查一次减 1，如果到 0 都不确认说明失败
    } dv_context;

    bool dv_available();
    void trigger_dv(const std::string_view& reason = "");
    void radar_info_callback(const radar_interface::msg::RadarInfo& info);
    void time_callback(const std_msgs::msg::UInt16& time);

    rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr pub_radar_cmd;
    rclcpp::Subscription<radar_interface::msg::RadarInfo>::SharedPtr sub_radar_info;
    rclcpp::Subscription<std_msgs::msg::UInt16>::SharedPtr sub_time;

public:
    DvTriggerNode();
};

