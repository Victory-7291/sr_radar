cmake_minimum_required(VERSION 3.8)
project(radar_warn)

# 默认使用C++17标准
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找依赖包
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

# 查找OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 包含头文件目录
include_directories(
  include
  ${CMAKE_CURRENT_SOURCE_DIR}/../tdt_vision
)

# 编译可执行文件
ament_auto_add_executable(radar_warn_node
  src/radar_warn_node.cpp
)

# 链接依赖库
target_link_libraries(radar_warn_node
  ${OpenCV_LIBS}
)

# 安装可执行文件
install(TARGETS
  radar_warn_node
  DESTINATION lib/${PROJECT_NAME}
)

# 安装头文件
install(DIRECTORY
  include/
  DESTINATION include
)

# 安装启动文件
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
  OPTIONAL
)

# 安装配置文件(如果有)
install(DIRECTORY
  config
  DESTINATION share/${PROJECT_NAME}/
  OPTIONAL
)

ament_auto_package() 