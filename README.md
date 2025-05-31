wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ colcon build
Starting >>> radar_interface
Starting >>> vision_interface
Starting >>> hik_camera
Starting >>> libocsort
Starting >>> video_player
Starting >>> video_recorder
Starting >>> video_streamer_cpp
Finished <<< vision_interface [6.55s]                                    
Finished <<< hik_camera [6.62s]
Finished <<< video_streamer_cpp [8.18s]                                  
Finished <<< libocsort [8.35s]                                            
Finished <<< radar_interface [8.45s]                                   
Starting >>> tdt_vision
Starting >>> debug_map
Starting >>> dv_trigger
Starting >>> judge_bridge
Starting >>> kalman_filter
Starting >>> radar_decision
Starting >>> rosbag_player
Finished <<< radar_decision [0.91s]                                   
Finished <<< video_recorder [10.1s]                                     
Finished <<< video_player [11.2s]                                        
--- stderr: rosbag_player                                            
** WARNING ** io features related to pcap will be disabled
CMake Warning (dev) at /opt/ros/humble/share/ament_cmake_auto/cmake/ament_auto_find_build_dependencies.cmake:67 (find_package):
  Policy CMP0074 is not set: find_package uses <PackageName>_ROOT variables.
  Run "cmake --help-policy CMP0074" for policy details.  Use the cmake_policy
  command to set the policy and suppress this warning.

  CMake variable PCL_ROOT is set to:

    /usr

  For compatibility, CMake is ignoring the variable.
Call Stack (most recent call first):
  CMakeLists.txt:37 (ament_auto_find_build_dependencies)
This warning is for project developers.  Use -Wno-dev to suppress it.

/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp: In member function ‘void RosbagPlayer::handle_bool_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage>, rclcpp::Time, rclcpp::Publisher<std_msgs::msg::Bool_<std::allocator<void> > >::SharedPtr)’:
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:124:111: warning: unused parameter ‘ros_time’ [-Wunused-parameter]
  124 | bag2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time,
      |                                                  ~~~~~~~~~~~~~^~~~~~~~

/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp: In member function ‘void RosbagPlayer::handle_uint16_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage>, rclcpp::Time)’:
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:134:113: warning: unused parameter ‘ros_time’ [-Wunused-parameter]
  134 | g2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
      |                                                ~~~~~~~~~~~~~^~~~~~~~

/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp: In member function ‘void RosbagPlayer::handle_uint8_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage>, rclcpp::Time)’:
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:143:112: warning: unused parameter ‘ros_time’ [-Wunused-parameter]
  143 | g2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
      |                                                ~~~~~~~~~~~~~^~~~~~~~

/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp: In member function ‘void RosbagPlayer::handle_game_robot_hp_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage>, rclcpp::Time)’:
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:152:120: warning: unused parameter ‘ros_time’ [-Wunused-parameter]
  152 | g2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
      |                                                ~~~~~~~~~~~~~^~~~~~~~

/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp: In member function ‘void RosbagPlayer::handle_radar_info_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage>, rclcpp::Time)’:
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:161:117: warning: unused parameter ‘ros_time’ [-Wunused-parameter]
  161 | g2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
      |                                                ~~~~~~~~~~~~~^~~~~~~~

/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp: In member function ‘void RosbagPlayer::handle_radar_mark_data_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage>, rclcpp::Time)’:
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:170:122: warning: unused parameter ‘ros_time’ [-Wunused-parameter]
  170 | g2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
      |                                                ~~~~~~~~~~~~~^~~~~~~~

/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp: In member function ‘void RosbagPlayer::play_bag()’:
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:218:82: error: no matching function for call to ‘rclcpp::Duration::Duration(int64_t&)’
  218 |         auto target_time = start_time + rclcpp::Duration(wait_time_ns);
      |                                                                      ^

In file included from /opt/ros/humble/include/rclcpp/rclcpp/qos.hpp:20,
                 from /opt/ros/humble/include/rclcpp/rclcpp/node_interfaces/node_graph_interface.hpp:32,
                 from /opt/ros/humble/include/rclcpp/rclcpp/client.hpp:42,
                 from /opt/ros/humble/include/rclcpp/rclcpp/callback_group.hpp:24,
                 from /opt/ros/humble/include/rclcpp/rclcpp/any_executable.hpp:20,
                 from /opt/ros/humble/include/rclcpp/rclcpp/memory_strategy.hpp:25,
                 from /opt/ros/humble/include/rclcpp/rclcpp/memory_strategies.hpp:18,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executor_options.hpp:20,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executor.hpp:37,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executors/multi_threaded_executor.hpp:25,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executors.hpp:21,
                 from /opt/ros/humble/include/rclcpp/rclcpp/rclcpp.hpp:155,
                 from /home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:1:
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:48:3: note: candidate: ‘template<class Rep, class Period> rclcpp::Duration::Duration(const std::chrono::duration<_Rep1, _Period1>&)’
   48 |   Duration(const std::chrono::duration<Rep, Period> & duration)  // NOLINT(runtime/explicit)
      |   ^~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:48:3: note:   template argument deduction/substitution failed:
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:218:82: note:   mismatched types ‘const std::chrono::duration<_Rep1, _Period1>’ and ‘int64_t’ {aka ‘long int’}
  218 |         auto target_time = start_time + rclcpp::Duration(wait_time_ns);
      |                                                                      ^

In file included from /opt/ros/humble/include/rclcpp/rclcpp/qos.hpp:20,
                 from /opt/ros/humble/include/rclcpp/rclcpp/node_interfaces/node_graph_interface.hpp:32,
                 from /opt/ros/humble/include/rclcpp/rclcpp/client.hpp:42,
                 from /opt/ros/humble/include/rclcpp/rclcpp/callback_group.hpp:24,
                 from /opt/ros/humble/include/rclcpp/rclcpp/any_executable.hpp:20,
                 from /opt/ros/humble/include/rclcpp/rclcpp/memory_strategy.hpp:25,
                 from /opt/ros/humble/include/rclcpp/rclcpp/memory_strategies.hpp:18,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executor_options.hpp:20,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executor.hpp:37,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executors/multi_threaded_executor.hpp:25,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executors.hpp:21,
                 from /opt/ros/humble/include/rclcpp/rclcpp/rclcpp.hpp:155,
                 from /home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:1:
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:151:3: note: candidate: ‘rclcpp::Duration::Duration()’
  151 |   Duration() = default;
      |   ^~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:151:3: note:   candidate expects 0 arguments, 1 provided
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:61:3: note: candidate: ‘rclcpp::Duration::Duration(const rclcpp::Duration&)’
   61 |   Duration(const Duration & rhs);
      |   ^~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:61:29: note:   no known conversion for argument 1 from ‘int64_t’ {aka ‘long int’} to ‘const rclcpp::Duration&’
   61 |   Duration(const Duration & rhs);
      |            ~~~~~~~~~~~~~~~~~^~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:59:12: note: candidate: ‘rclcpp::Duration::Duration(const rcl_duration_t&)’
   59 |   explicit Duration(const rcl_duration_t & duration);
      |            ^~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:59:44: note:   no known conversion for argument 1 from ‘int64_t’ {aka ‘long int’} to ‘const rcl_duration_t&’ {aka ‘const rcl_duration_s&’}
   59 |   explicit Duration(const rcl_duration_t & duration);
      |                     ~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:53:3: note: candidate: ‘rclcpp::Duration::Duration(const Duration&)’
   53 |   Duration(const builtin_interfaces::msg::Duration & duration_msg);  // NOLINT(runtime/explicit)
      |   ^~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:53:54: note:   no known conversion for argument 1 from ‘int64_t’ {aka ‘long int’} to ‘const Duration&’ {aka ‘const builtin_interfaces::msg::Duration_<std::allocator<void> >&’}
   53 |   Duration(const builtin_interfaces::msg::Duration & duration_msg);  // NOLINT(runtime/explicit)
      |            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:42:12: note: candidate: ‘rclcpp::Duration::Duration(std::chrono::nanoseconds)’
   42 |   explicit Duration(std::chrono::nanoseconds nanoseconds);
      |            ^~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:42:46: note:   no known conversion for argument 1 from ‘int64_t’ {aka ‘long int’} to ‘std::chrono::nanoseconds’ {aka ‘std::chrono::duration<long int, std::ratio<1, 1000000000> >’}
   42 |   explicit Duration(std::chrono::nanoseconds nanoseconds);
      |                     ~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:39:3: note: candidate: ‘rclcpp::Duration::Duration(int32_t, uint32_t)’
   39 |   Duration(int32_t seconds, uint32_t nanoseconds);
      |   ^~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/duration.hpp:39:3: note:   candidate expects 2 arguments, 1 provided
gmake[2]: *** [CMakeFiles/rosbag_player.dir/build.make:76: CMakeFiles/rosbag_player.dir/rosbag_player.cpp.o] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:139: CMakeFiles/rosbag_player.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2
---
Failed   <<< rosbag_player [9.30s, exited with code 2]
Aborted  <<< dv_trigger [10.1s]                   
Aborted  <<< debug_map [14.7s]                     
Aborted  <<< kalman_filter [15.4s]                 
Aborted  <<< judge_bridge [15.6s]                  
Aborted  <<< tdt_vision [40.8s]                                    

Summary: 8 packages finished [49.4s]
  1 package failed: rosbag_player
  5 packages aborted: debug_map dv_trigger judge_bridge kalman_filter tdt_vision
  2 packages had stderr output: rosbag_player tdt_vision
  1 package not processed
wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ 


