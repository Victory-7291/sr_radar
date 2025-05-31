wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ colcon build
Starting >>> radar_interface
Starting >>> vision_interface
Starting >>> hik_camera
Starting >>> libocsort
Starting >>> video_player
Starting >>> video_recorder
Starting >>> video_streamer_cpp
Finished <<< video_recorder [0.12s]                                                                                                      
Finished <<< libocsort [0.13s]
Finished <<< hik_camera [0.15s]
Finished <<< video_streamer_cpp [0.15s]
Finished <<< video_player [0.16s]
Finished <<< vision_interface [0.28s]                                                                      
Finished <<< radar_interface [0.30s]
Starting >>> tdt_vision
Starting >>> debug_map
Starting >>> dv_trigger
Starting >>> judge_bridge
Starting >>> kalman_filter
Starting >>> radar_decision
Starting >>> rosbag_player
Finished <<< radar_decision [0.06s]
Finished <<< debug_map [0.09s]
Finished <<< dv_trigger [0.10s]                                                                                                 
Finished <<< rosbag_player [0.10s]
Finished <<< kalman_filter [0.12s]
Finished <<< tdt_vision [0.16s]
Starting >>> radar_warn
Finished <<< radar_warn [0.08s]                                                              
--- stderr: judge_bridge                               
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
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/judge_bridge.hpp:6,
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:1:
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp: In member function ‘void JudgeBridgeNode::filter_handler(JudgeBridge::JudgeSerial::JudgePair)’:
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:25:60: error: expected ‘)’ before ‘mark_data’
   25 |         RCLCPP_INFO(get_logger(), "mark hero progress: %f" mark_data->mark_hero_progress);
      |                                                            ^~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:25:9: note: to match this ‘(’
   25 |         RCLCPP_INFO(get_logger(), "mark hero progress: %f" mark_data->mark_hero_progress);
      |         ^~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:25:35: warning: format ‘%f’ expects a matching ‘double’ argument [-Wformat=]
   25 |         RCLCPP_INFO(get_logger(), "mark hero progress: %f" mark_data->mark_hero_progress);
      |                                   ^~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:25:57: note: format string is defined here
   25 |         RCLCPP_INFO(get_logger(), "mark hero progress: %f" mark_data->mark_hero_progress);
      |                                                        ~^
      |                                                         |
      |                                                         double
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
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/judge_bridge.hpp:6,
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:1:
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:26:64: error: expected ‘)’ before ‘mark_data’
   26 |         RCLCPP_INFO(get_logger(), "mark engineer progress: %f" mark_data->mark_engineer_progress);
      |                                                                ^~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:26:9: note: to match this ‘(’
   26 |         RCLCPP_INFO(get_logger(), "mark engineer progress: %f" mark_data->mark_engineer_progress);
      |         ^~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:26:35: warning: format ‘%f’ expects a matching ‘double’ argument [-Wformat=]
   26 |         RCLCPP_INFO(get_logger(), "mark engineer progress: %f" mark_data->mark_engineer_progress);
      |                                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:26:61: note: format string is defined here
   26 |         RCLCPP_INFO(get_logger(), "mark engineer progress: %f" mark_data->mark_engineer_progress);
      |                                                            ~^
      |                                                             |
      |                                                             double
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
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/judge_bridge.hpp:6,
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:1:
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:27:66: error: expected ‘)’ before ‘mark_data’
   27 |         RCLCPP_INFO(get_logger(), "mark standard 3 progress: %f" mark_data->mark_standard_3_progress);
      |                                                                  ^~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:27:9: note: to match this ‘(’
   27 |         RCLCPP_INFO(get_logger(), "mark standard 3 progress: %f" mark_data->mark_standard_3_progress);
      |         ^~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:27:35: warning: format ‘%f’ expects a matching ‘double’ argument [-Wformat=]
   27 |         RCLCPP_INFO(get_logger(), "mark standard 3 progress: %f" mark_data->mark_standard_3_progress);
      |                                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:27:63: note: format string is defined here
   27 |         RCLCPP_INFO(get_logger(), "mark standard 3 progress: %f" mark_data->mark_standard_3_progress);
      |                                                              ~^
      |                                                               |
      |                                                               double
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
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/judge_bridge.hpp:6,
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:1:
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:28:66: error: expected ‘)’ before ‘mark_data’
   28 |         RCLCPP_INFO(get_logger(), "mark standard 4 progress: %f" mark_data->mark_standard_4_progress);
      |                                                                  ^~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:28:9: note: to match this ‘(’
   28 |         RCLCPP_INFO(get_logger(), "mark standard 4 progress: %f" mark_data->mark_standard_4_progress);
      |         ^~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:28:35: warning: format ‘%f’ expects a matching ‘double’ argument [-Wformat=]
   28 |         RCLCPP_INFO(get_logger(), "mark standard 4 progress: %f" mark_data->mark_standard_4_progress);
      |                                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:28:63: note: format string is defined here
   28 |         RCLCPP_INFO(get_logger(), "mark standard 4 progress: %f" mark_data->mark_standard_4_progress);
      |                                                              ~^
      |                                                               |
      |                                                               double
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
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/judge_bridge.hpp:6,
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:1:
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:29:62: error: expected ‘)’ before ‘mark_data’
   29 |         RCLCPP_INFO(get_logger(), "mark sentry progress: %f" mark_data->mark_sentry_progress);
      |                                                              ^~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:29:9: note: to match this ‘(’
   29 |         RCLCPP_INFO(get_logger(), "mark sentry progress: %f" mark_data->mark_sentry_progress);
      |         ^~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:29:35: warning: format ‘%f’ expects a matching ‘double’ argument [-Wformat=]
   29 |         RCLCPP_INFO(get_logger(), "mark sentry progress: %f" mark_data->mark_sentry_progress);
      |                                   ^~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:29:59: note: format string is defined here
   29 |         RCLCPP_INFO(get_logger(), "mark sentry progress: %f" mark_data->mark_sentry_progress);
      |                                                          ~^
      |                                                           |
      |                                                           double
gmake[2]: *** [CMakeFiles/judge_bridge.dir/build.make:76: CMakeFiles/judge_bridge.dir/src/judge_bridge.cpp.o] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:137: CMakeFiles/judge_bridge.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2
---
Failed   <<< judge_bridge [5.20s, exited with code 2]

Summary: 14 packages finished [5.67s]
  1 package failed: judge_bridge
  1 package had stderr output: judge_bridge
wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ 


