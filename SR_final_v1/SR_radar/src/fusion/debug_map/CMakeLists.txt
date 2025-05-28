cmake_minimum_required(VERSION 3.8)
project(debug_map)

find_package (ament_cmake_auto REQUIRED) 

# 添加radar_interface包的查找
find_package(radar_interface REQUIRED)
find_package(rclcpp_components REQUIRED)

ament_auto_find_build_dependencies ()

# 创建组件库
add_library(${PROJECT_NAME} SHARED debug_map.cpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE "COMPOSITION_BUILDING_DLL")

# 添加对radar_interface的链接
ament_target_dependencies(debug_map
  rclcpp
  rclcpp_components
  vision_interface
  sensor_msgs
  cv_bridge
  radar_interface
)

# 注册组件
rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "tdt_radar::DebugMap"
  EXECUTABLE ${PROJECT_NAME}_node
)

# 安装
install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_auto_package ()