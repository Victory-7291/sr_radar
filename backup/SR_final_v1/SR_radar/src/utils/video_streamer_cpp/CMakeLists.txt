cmake_minimum_required(VERSION 3.8)
project(video_streamer_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(image_transport REQUIRED)

# Include directories
include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
)

# Define the component library
add_library(${PROJECT_NAME} SHARED
  src/video_streamer_node.cpp
)

# Set target compile definitions (needed for component visibility)
target_compile_definitions(${PROJECT_NAME} PRIVATE "COMPOSITION_BUILDING_DLL")

# Link dependencies
ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  rclcpp_components
  sensor_msgs
  cv_bridge
  image_transport
)

target_link_libraries(${PROJECT_NAME}
  ${OpenCV_LIBRARIES}
)

# Register the component with rclcpp_components
rclcpp_components_register_nodes(${PROJECT_NAME}
  "video_streamer_cpp::VideoStreamerNode"
)

# Install targets
install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install include directory
install(DIRECTORY
  include/
  DESTINATION include/
)

# Install launch files if any (optional for now)
# install(DIRECTORY launch
#   DESTINATION share/${PROJECT_NAME}/launch)

# Linters
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package() 