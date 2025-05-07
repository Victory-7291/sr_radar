cmake_minimum_required(VERSION 3.10)
project(libocsort)

# Removed Windows-specific /O2 flags for broader compatibility
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2") # Example for GCC/Clang
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")   # Example for GCC/Clang

set(CMAKE_CXX_STANDARD 17)

# Linker external library
# Assuming Eigen3 and OpenCV are found by the parent CMakeLists.txt or are system-wide
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED) # OpenCV might be needed for the test executable, not necessarily the libocsort library itself.

# add_subdirectory(src)
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # Specific to Windows, commented out for broader compatibility
file(GLOB SRC_LIST src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)

# 注释掉测试程序的构建
# note：test with yolo inference
# add_executable(ocsort_test mutilthread.cpp ../detector/inference.h ../detector/inference.cpp)
# target_link_libraries(ocsort_test PUBLIC Eigen3::Eigen ${PROJECT_NAME} OpenCV::opencv_core OpenCV::opencv_highgui OpenCV::opencv_imgproc)


