cmake_minimum_required(VERSION 3.8)
project(radar_decision)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

# Add executable or library targets here if needed
# Example:
# file(GLOB_RECURSE src "src/**.cpp")
# ament_auto_add_executable(${PROJECT_NAME} ${src})
# target_link_libraries(${PROJECT_NAME} ...)

# Install targets (e.g., executables, libraries, headers)
# Example:
# install(
#   TARGETS ${PROJECT_NAME}
#   DESTINATION lib/${PROJECT_NAME}
# )

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()