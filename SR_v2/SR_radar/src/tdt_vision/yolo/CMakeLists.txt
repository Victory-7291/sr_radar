cmake_minimum_required(VERSION 3.10)
cMAKE_policy(SET CMP0079 NEW)
cMAKE_policy(SET CMP0104 NEW)

set(CMAKE_CUDA_ARCHITECTURES 50 52 61 75)
#set(CMAKE_CUDA_COMPILER /usr/local/cuda-12.4/bin/nvcc)
#set(nvinfer_LIBRARY "/home/wan/TensorRT-10.7.0.23/lib/libnvinfer.so")
#set(nvinfer_INCLUDE_DIRS "/home/wan/TensorRT-10.7.0.23/include")
project(yolo)
add_definitions(-std=c++11)
add_definitions(-DAPI_EXPORTS)
option(CUDA_USE_STATIC_CUDA_RUNTIME ON)
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
# TODO(Call for PR): make cmake compatible with Windows
include_directories(/home/wan/TensorRT-10.7.0.23/include/)
link_directories(/home/wan/TensorRT-10.7.0.23/lib/)
find_package(CUDA)

# include and link dirs of cuda and tensorrt, you need adapt them if yours are different
# cuda
include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${nvinfer_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.cu)
add_library(yolo  ${SRCS})
target_link_libraries(yolo ${nvinfer_LIBRARY} cudart nvonnxparser ${OpenCV_LIBS})
