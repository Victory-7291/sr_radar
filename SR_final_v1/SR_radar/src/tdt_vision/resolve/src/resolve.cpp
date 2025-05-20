#include "resolve.h"

#define TDT_INFO(msg) std::cout << msg << std::endl

namespace tdt_radar {

Resolve::Resolve(const rclcpp::NodeOptions& node_options) : Node("radar_resolve_node", node_options) {
  parser_ = new parser();
  minimap=cv::imread("configa/RM2024.png");
  
  point_sub = this->create_subscription<geometry_msgs::msg::Vector3>("camera_point2D", rclcpp::SensorDataQoS(),std::bind(&Resolve::callback, this, std::placeholders::_1));
  pub = this->create_publisher<sensor_msgs::msg::PointCloud2>("camera_point3D", rclcpp::SensorDataQoS());
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


void Resolve::callback(const geometry_msgs::msg::Vector3::SharedPtr msg) {
  cv::Point2f point;
  point.x = msg->x;
  point.y = msg->y;
  auto center_point=parser_->parse(point);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointXYZ send_point;
  send_point.x = center_point.x;
  send_point.y = 15-center_point.y;
  std::cout<<center_point<<std::endl;
  send_point.z = 1;
  cloud->points.push_back(send_point);
  sensor_msgs::msg::PointCloud2 output;
  pcl::toROSMsg(*cloud, output);
  output.header.frame_id = "rm_frame";
  pub->publish(output);
  }

void Resolve::DetectCallback(const vision_interface::msg::DetectResult::SharedPtr msg) {
  cv::Mat Map_clone=minimap.clone();
  std::vector<map_car> cars;
  //这个节点的功能是
  //1.解算
  //2.可视化
  vision_interface::msg::DetectResult send_data;
  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
  for(int i=0;i<6;i++){
    cv::Point2f blue_point;
    blue_point.x = msg->blue_x[i];
    blue_point.y = msg->blue_y[i];
    if(blue_point.x*blue_point.y){
      auto center_point=parser_->parse(blue_point);
      center_point.y=15+center_point.y;
      // center_point.x=center_point.x+=6;
      // center_point.y=center_point.y-=4;
      send_data.blue_x[i]=center_point.x;
      send_data.blue_y[i]=center_point.y;
      pcl::PointXYZRGBA send_point;
      send_point.x = center_point.x;
      send_point.y = center_point.y;
      send_point.z = 1;
      send_point.r = 0;
      send_point.g = 0;
      send_point.b = 255;
      send_point.a = 255;
      cloud->points.push_back(send_point);
      cv::circle(Map_clone,cv::Point((Map_clone.cols*center_point.x)/28,Map_clone.rows*(15-center_point.y)/15),20,cv::Scalar(200,0,0),-1);
      cv::putText(Map_clone,std::to_string(i+1),cv::Point((Map_clone.cols*center_point.x)/28-10,Map_clone.rows*(15-center_point.y)/15+10),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(255,255,255),2);
    }
    cv::Point2f red_point;
    red_point.x = msg->red_x[i];
    red_point.y = msg->red_y[i];
    if(red_point.x*red_point.y){
      auto center_point=parser_->parse(red_point);
      center_point.y=15+center_point.y;
      // center_point.x=center_point.x+=6;
      // center_point.y=center_point.y-=4;
      send_data.red_x[i]=center_point.x;
      send_data.red_y[i]=center_point.y;
      pcl::PointXYZRGBA send_point;
      send_point.x = center_point.x;
      send_point.y = center_point.y;
      send_point.z = 1;
      send_point.r = 255;
      send_point.g = 0;
      send_point.b = 0;
      send_point.a = 255;
      cloud->points.push_back(send_point);
      cv::circle(Map_clone,cv::Point((Map_clone.cols*center_point.x)/28,Map_clone.rows*(15-center_point.y)/15),20,cv::Scalar(0,0,200),-1);
      cv::putText(Map_clone,std::to_string(i+1),cv::Point((Map_clone.cols*center_point.x)/28-10,Map_clone.rows*(15-center_point.y)/15+10),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(255,255,255),2);
    }
  }

  send_data.header.stamp=msg->header.stamp;
  pub_radar->publish(send_data);
  auto cloud_msg = sensor_msgs::msg::PointCloud2();
  pcl::toROSMsg(*cloud, cloud_msg);
  cloud_msg.header.frame_id = "rm_frame";
  cloud_msg.header.stamp = msg->header.stamp;
  pub->publish(cloud_msg);
} 
} // namespace tdt_radar
RCLCPP_COMPONENTS_REGISTER_NODE(tdt_radar::Resolve)