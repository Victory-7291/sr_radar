#include "resolve.h"

#define TDT_INFO(msg) std::cout << msg << std::endl

namespace tdt_radar {

Resolve::Resolve(const rclcpp::NodeOptions& node_options) : Node("radar_resolve_node", node_options) {
  parser_ = new parser();
  
  detect_sub = this->create_subscription<vision_interface::msg::DetectResult>("detect_result", rclcpp::SensorDataQoS(),std::bind(&Resolve::DetectCallback, this, std::placeholders::_1));
  pub_radar=this->create_publisher<vision_interface::msg::DetectResult>("/resolve_result",rclcpp::SensorDataQoS());
  
  // 添加新的订阅
  radar_mark_data_sub = this->create_subscription<radar_interface::msg::RadarMarkData>(
    "judge/radar_mark_data", rclcpp::SystemDefaultsQoS(), 
    std::bind(&Resolve::RadarMarkDataCallback, this, std::placeholders::_1));
  
  game_robot_hp_sub = this->create_subscription<radar_interface::msg::GameRobotHP>(
    "judge/game_robot_hp", rclcpp::SystemDefaultsQoS(), 
    std::bind(&Resolve::GameRobotHPCallback, this, std::placeholders::_1));
  
  remain_time_sub = this->create_subscription<std_msgs::msg::UInt16>(
    "judge/remain_time", rclcpp::SystemDefaultsQoS(), 
    std::bind(&Resolve::RemainTimeCallback, this, std::placeholders::_1));
  
  // 初始化数据
  match_time = 0;
  for (int i = 0; i < 6; i++) {
    markers[i] = 0;
  }
  for (int i = 0; i < 16; i++) {
    robot_hp[i] = 0;
  }
  
  TDT_INFO("Load radar resolve node success!");
}

void Resolve::RadarMarkDataCallback(const radar_interface::msg::RadarMarkData::SharedPtr msg) {
  for (int i = 0; i < 6; i++) {
    markers[i] = msg->mark_progress[i];
  }
  RCLCPP_INFO(this->get_logger(), "Received radar mark data");
}

void Resolve::GameRobotHPCallback(const radar_interface::msg::GameRobotHP::SharedPtr msg) {
  // 红方机器人血量 (0-5)
  for (int i = 0; i < 6; i++) {
    robot_hp[i] = msg->red_robot_hp[i];
  }
  // 蓝方机器人血量 (8-13)
  for (int i = 0; i < 6; i++) {
    robot_hp[i + 8] = msg->blue_robot_hp[i];
  }
  // 红方前哨站和基地 (6-7)
  robot_hp[6] = msg->red_outpost;
  robot_hp[7] = msg->red_base;
  // 蓝方前哨站和基地 (14-15)
  robot_hp[14] = msg->blue_outpost;
  robot_hp[15] = msg->blue_base;
  
  RCLCPP_INFO(this->get_logger(), "Received game robot HP data");
}

void Resolve::RemainTimeCallback(const std_msgs::msg::UInt16::SharedPtr msg) {
  match_time = msg->data;
  RCLCPP_INFO(this->get_logger(), "Received remain time: %d", match_time);
}


void Resolve::DetectCallback(const vision_interface::msg::DetectResult::SharedPtr msg) {
  std::vector<map_car> cars;
  //这个节点的功能是
  //1.解算
  //2.可视化
  vision_interface::msg::DetectResult send_data;
  for(int i=0;i<6;i++){
    cv::Point2f blue_point;
    blue_point.x = msg->blue_x[i];
    blue_point.y = msg->blue_y[i];
    if(blue_point.x*blue_point.y){
      auto center_point=parser_->parse(blue_point);
      center_point.y=15+center_point.y;
      send_data.blue_x[i]=center_point.x;
      send_data.blue_y[i]=center_point.y;
    }
    cv::Point2f red_point;
    red_point.x = msg->red_x[i];
    red_point.y = msg->red_y[i];
    if(red_point.x*red_point.y){
      auto center_point=parser_->parse(red_point);
      center_point.y=15+center_point.y;
      send_data.red_x[i]=center_point.x;
      send_data.red_y[i]=center_point.y;
    }
  }

  send_data.header.stamp=msg->header.stamp;
  pub_radar->publish(send_data);
  
} 
} // namespace tdt_radar
RCLCPP_COMPONENTS_REGISTER_NODE(tdt_radar::Resolve)