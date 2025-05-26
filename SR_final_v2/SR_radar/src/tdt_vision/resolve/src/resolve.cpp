#include "resolve.h"

#define TDT_INFO(msg) std::cout << msg << std::endl

namespace tdt_radar {

Resolve::Resolve(const rclcpp::NodeOptions& node_options) : Node("radar_resolve_node", node_options) {
  parser_ = new parser();
  
  detect_sub = this->create_subscription<vision_interface::msg::DetectResult>("detect_result", rclcpp::SensorDataQoS(),std::bind(&Resolve::DetectCallback, this, std::placeholders::_1));
  pub_radar=this->create_publisher<vision_interface::msg::DetectResult>("/resolve_result",rclcpp::SensorDataQoS());
  
  TDT_INFO("Load radar resolve node success!");
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