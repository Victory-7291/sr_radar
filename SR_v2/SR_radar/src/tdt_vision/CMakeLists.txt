cmake_minimum_required(VERSION 3.8)
project(tdt_vision)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# openvino tensort用，编译动态库时，符号表对只读文件重映射，需要添加此指令
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include_directories(/home/wan/TensorRT-10.7.0.23/include/)
link_directories(/home/wan/TensorRT-10.7.0.23/lib/)
set(nvinfer_LIBRARY "/home/wan/TensorRT-10.7.0.23/lib/libnvinfer.so")


execute_process(COMMAND export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/wan/TensorRT-10.0.0.6/lib)
# 包含头文件
include_directories(  
  "detect/include"
  "resolve/include"
  "calibrate/include"
  "radar_utils"
  "yolo"
)
option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CUDA_COMPILER /usr/local/cuda-12.4/bin/nvcc)
set(CUDA_INCLUDE_DIRS "/usr/local/cuda-12.4/include")
include_directories(/usr/local/cuda-12.4/include)
link_directories(/usr/local/cuda-12.4/lib64)
#set(nvinfer_INCLUDE_DIRS "/home/wan/TensorRT-10.7.0.23/include")
#set(nvinfer_LIBRARY "/home/wan/TensorRT-10.7.0.23/lib")
#link_directories(/home/wan/TensorRT-10.0.0.6/lib)
#include_directories(/home/wan/TensorRT-10.0.0.6/include)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_subdirectory(OCSort)

file(GLOB_RECURSE RADAR_UTILS_SRCS "radar_utils/*.cpp")

ament_auto_add_library(radar_utils SHARED
    ${RADAR_UTILS_SRCS}
)

set(RADAR_DETECT "radar_detect")
file(GLOB_RECURSE RADAR_DETECT_SRCS "detect/src/*.cpp")
add_library(${RADAR_DETECT} SHARED
    ${RADAR_DETECT_SRCS}
)
target_include_directories(${RADAR_DETECT} PUBLIC
  "detect/include"
)

# 添加ament依赖
ament_target_dependencies(${RADAR_DETECT}
  "rclcpp"
  "rclcpp_components"
  "std_msgs"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
  "vision_interface"
  "geometry_msgs"
)

find_package(CUDA)
include(${PROJECT_SOURCE_DIR}/cmake/modules/libnvinferConfig.cmake)
message("Using Cuda Version: ${CUDA_VERSION} and TensorRT Version: ${nvinfer_VERSION}")
add_definitions(-D use_tensorrt)
enable_language(CUDA)
include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${nvinfer_INCLUDE_DIRS})
add_subdirectory(yolo)
include_directories(${PROJECT_SOURCE_DIR}/yolo)

target_link_libraries(${RADAR_DETECT}
    libocsort
    Eigen3::Eigen
    ${OpenCV_LIBS}
    yolo 
    ${nvinfer_LIBRARY} 
    cudart 
    nvonnxparser 
    fmt 
    ${PCL_LIBRARIES}
)

# 确保组件属性正确设置
set_target_properties(${RADAR_DETECT} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}"
)
rclcpp_components_register_node(${RADAR_DETECT}
    PLUGIN "tdt_radar::Detect"
    EXECUTABLE ${RADAR_DETECT}_node
)

set(RADAR_RESOLVE "radar_resolve")
file(GLOB_RECURSE RADAR_RESOLVE_SRCS "resolve/src/*.cpp")

add_library(${RADAR_RESOLVE} SHARED
    ${RADAR_RESOLVE_SRCS}
)
target_include_directories(${RADAR_RESOLVE} PUBLIC
  "resolve/include"
)

# 添加ament依赖
ament_target_dependencies(${RADAR_RESOLVE}
  "rclcpp"
  "rclcpp_components"
  "std_msgs"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
  "vision_interface"
  "geometry_msgs"
)

# 设置组件属性
set_target_properties(${RADAR_RESOLVE} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}"
)
rclcpp_components_register_node(${RADAR_RESOLVE}
    PLUGIN "tdt_radar::Resolve"
    EXECUTABLE ${RADAR_RESOLVE}_node
)

set(RADAR_CALIBRATE "radar_calibrate")
file(GLOB_RECURSE RADAR_CALIBRATE_SRCS "calibrate/src/*.cpp")
add_library(${RADAR_CALIBRATE} SHARED
    ${RADAR_CALIBRATE_SRCS}
)
target_include_directories(${RADAR_CALIBRATE} PUBLIC
  "calibrate/include"
)

# 添加ament依赖
ament_target_dependencies(${RADAR_CALIBRATE}
  "rclcpp"
  "rclcpp_components"
  "std_msgs"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
  "vision_interface"
  "geometry_msgs"
)

# 设置组件属性
set_target_properties(${RADAR_CALIBRATE} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}"
)
rclcpp_components_register_node(${RADAR_CALIBRATE}
    PLUGIN "tdt_radar::Calibrate"
    EXECUTABLE ${RADAR_CALIBRATE}_node
)

ament_auto_package(
    INSTALL_TO_SHARE
    launch
)
