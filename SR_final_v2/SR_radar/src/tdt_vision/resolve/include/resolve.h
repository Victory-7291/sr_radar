#ifndef RADAR_RESOLVE_H
#define RADAR_RESOLVE_H

#include <geometry_msgs/msg/detail/point__struct.hpp>
#include <memory>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <sensor_msgs/msg/image.hpp>
#include "radar_utils.h"
#include "cv_bridge/cv_bridge.h"
#include "geometry_msgs/msg/vector3.hpp"
#include "opencv2/opencv.hpp"
#include "pcl/point_types.h"
#include "pcl_conversions/pcl_conversions.h"
#include "vision_interface/msg/detect_result.hpp"
#include <std_msgs/msg/u_int16.hpp>

namespace tdt_radar {

class Resolve final : public rclcpp::Node {
 public:
  explicit Resolve(const rclcpp::NodeOptions& options);
  void DetectCallback(const vision_interface::msg::DetectResult::SharedPtr msg);
  
  rclcpp::Subscription<vision_interface::msg::DetectResult>::SharedPtr detect_sub;
  
  parser* parser_;

 private:
  rclcpp::Publisher<vision_interface::msg::DetectResult>::SharedPtr pub_radar;
};

class map_car{
  public:
  float x;
  float y;
  int id;
};
}  // namespace tdt_radar

#endif