cmake_minimum_required(VERSION 3.8)
project(debug_map)

find_package (ament_cmake_auto REQUIRED) 

# 添加radar_interface包的查找
find_package(radar_interface REQUIRED)

ament_auto_find_build_dependencies ()

ament_auto_add_executable(debug_map debug_map.cpp)

# 添加对radar_interface的链接
ament_target_dependencies(debug_map
  rclcpp
  vision_interface
  sensor_msgs
  cv_bridge
  radar_interface
)

ament_auto_package ()