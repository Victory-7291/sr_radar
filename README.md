wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ colcon build
Starting >>> radar_interface
Starting >>> vision_interface
Starting >>> hik_camera
Starting >>> libocsort
Starting >>> video_player
Starting >>> video_recorder
Starting >>> video_streamer_cpp
Finished <<< libocsort [0.11s]                                                                                                           
Finished <<< video_recorder [0.12s]
Finished <<< hik_camera [0.14s]
Finished <<< video_streamer_cpp [0.15s]
Finished <<< video_player [0.17s]
Finished <<< vision_interface [0.28s]                                                                      
Finished <<< radar_interface [0.31s]                   
Starting >>> tdt_vision
Starting >>> debug_map
Starting >>> dv_trigger
Starting >>> judge_bridge
Starting >>> kalman_filter
Starting >>> radar_decision
Starting >>> rosbag_player
Finished <<< radar_decision [0.07s]
Finished <<< debug_map [0.10s]                                                                                             
Finished <<< dv_trigger [0.10s]
Finished <<< kalman_filter [0.11s]
Finished <<< judge_bridge [0.12s]
Finished <<< tdt_vision [0.16s]
Starting >>> radar_warn
Finished <<< radar_warn [0.08s]                                                               
--- stderr: rosbag_player                               
In file included from /opt/ros/humble/include/rclcpp/rclcpp/logging.hpp:24,
                 from /opt/ros/humble/include/rclcpp/rclcpp/client.hpp:40,
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
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp: In member function ‘void RosbagPlayer::handle_radar_mark_data_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage>, rclcpp::Time)’:
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:184:66: error: ‘using element_type = struct radar_interface::msg::RadarMarkData_<std::allocator<void> >’ {aka ‘struct radar_interface::msg::RadarMarkData_<std::allocator<void> >’} has no member named ‘mark_hero_progress’; did you mean ‘mark_progress’?
  184 |         RCLCPP_INFO(get_logger(), "mark hero progress: %f", msg->mark_hero_progress);
      |                                                                  ^~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:185:70: error: ‘using element_type = struct radar_interface::msg::RadarMarkData_<std::allocator<void> >’ {aka ‘struct radar_interface::msg::RadarMarkData_<std::allocator<void> >’} has no member named ‘mark_engineer_progress’
  185 |         RCLCPP_INFO(get_logger(), "mark engineer progress: %f", msg->mark_engineer_progress);
      |                                                                      ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:186:72: error: ‘using element_type = struct radar_interface::msg::RadarMarkData_<std::allocator<void> >’ {aka ‘struct radar_interface::msg::RadarMarkData_<std::allocator<void> >’} has no member named ‘mark_standard_3_progress’
  186 |         RCLCPP_INFO(get_logger(), "mark standard 3 progress: %f", msg->mark_standard_3_progress);
      |                                                                        ^~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:187:72: error: ‘using element_type = struct radar_interface::msg::RadarMarkData_<std::allocator<void> >’ {aka ‘struct radar_interface::msg::RadarMarkData_<std::allocator<void> >’} has no member named ‘mark_standard_4_progress’
  187 |         RCLCPP_INFO(get_logger(), "mark standard 4 progress: %f", msg->mark_standard_4_progress);
      |                                                                        ^~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:188:68: error: ‘using element_type = struct radar_interface::msg::RadarMarkData_<std::allocator<void> >’ {aka ‘struct radar_interface::msg::RadarMarkData_<std::allocator<void> >’} has no member named ‘mark_sentry_progress’; did you mean ‘mark_progress’?
  188 |         RCLCPP_INFO(get_logger(), "mark sentry progress: %f", msg->mark_sentry_progress);
      |                                                                    ^~~~~~~~~~~~~~~~~~~~
gmake[2]: *** [CMakeFiles/rosbag_player.dir/build.make:76: CMakeFiles/rosbag_player.dir/rosbag_player.cpp.o] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:139: CMakeFiles/rosbag_player.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2
---
Failed   <<< rosbag_player [3.14s, exited with code 2]

Summary: 14 packages finished [3.64s]
  1 package failed: rosbag_player
  1 package had stderr output: rosbag_player
wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ 


