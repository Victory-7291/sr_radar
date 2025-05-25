#include <memory>
#include <dv_trigger/dv_trigger.hpp>

DvTriggerNode::DvTriggerNode()
    : rclcpp::Node("dv_trigger")
{
    dv_context.used_chances = 0;
    dv_context.waiting_for_check = false;

    declare_parameter("dv_check_time", 5);
    declare_parameter("dv_max", 2);

    pub_radar_cmd = create_publisher<std_msgs::msg::UInt8>("judge/radar_cmd", rclcpp::SystemDefaultsQoS());
    
    sub_radar_info = create_subscription<radar_interface::msg::RadarInfo>("judge/radar_info", rclcpp::SystemDefaultsQoS(), std::bind(&DvTriggerNode::radar_info_callback, this, std::placeholders::_1));
}

bool DvTriggerNode::dv_available()
{
    return !dv_context.is_dv_trigered && (dv_context.now_chances > dv_context.used_chances);
}

void DvTriggerNode::trigger_dv(const std::string_view& reason)
{
    if (!dv_available()) {
        RCLCPP_WARN(get_logger(), "Trigger Failed. Trigger reason: %s", reason.data());
        return;
    }
    auto radar_cmd = std_msgs::msg::UInt8();
    radar_cmd.data = std::min(long(dv_context.used_chances + 1), get_parameter("dv_max").as_int());
    dv_context.waiting_for_check = get_parameter("dv_check_time").as_int();
    pub_radar_cmd->publish(radar_cmd);

    RCLCPP_INFO(get_logger(), "Trigger double vulnerability: %d / %d, reason: %s", dv_context.used_chances, dv_context.now_chances, reason.data());
}

void DvTriggerNode::radar_info_callback(const radar_interface::msg::RadarInfo& info){
    dv_context.now_chances = info.dv_chances;
    dv_context.is_dv_trigered = info.dv_triggered;

    if (dv_context.waiting_for_check > 0) {
        if (dv_context.is_dv_trigered) {
            dv_context.waiting_for_check = 0;
            ++dv_context.used_chances;
            RCLCPP_INFO(get_logger(), "Double vulnerability successfully triggered");
        }
        else
            --dv_context.waiting_for_check;
    }
    if (dv_context.used_chances > info.dv_chances) {
        dv_context.used_chances = info.dv_chances;
        RCLCPP_WARN(get_logger(), "Double vulnerability has wrong response");
    }
    if (!dv_context.is_dv_trigered && dv_context.now_chances > dv_context.used_chances && dv_context.waiting_for_check == 0) {
        trigger_dv("自动触发");
    }
}
