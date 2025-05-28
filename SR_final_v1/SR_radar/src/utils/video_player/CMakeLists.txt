# Video player for ROS2 
cmake_minimum_required(VERSION 3.8)
project(video_player)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(image_transport REQUIRED)

include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
)

set(dependencies
  rclcpp
  rclcpp_components
  sensor_msgs
  cv_bridge
  image_transport
)

add_library(${PROJECT_NAME} SHARED
  src/video_player_node.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(${PROJECT_NAME} ${dependencies})

rclcpp_components_register_nodes(${PROJECT_NAME}
  "video_player::VideoPlayerNode"
)

add_executable(video_player_node src/video_player_node.cpp)
ament_target_dependencies(video_player_node ${dependencies})

target_link_libraries(video_player_node ${OpenCV_LIBRARIES})

install(TARGETS
  ${PROJECT_NAME}
  video_player_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  include/
  DESTINATION include
)

# 安装launch文件
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()