wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ colcon build
Starting >>> radar_interface
Starting >>> vision_interface
Starting >>> hik_camera
Starting >>> libocsort
Starting >>> video_player
Finished <<< libocsort [0.08s]
Finished <<< video_player [0.10s]                                        
Finished <<< hik_camera [0.11s]
Finished <<< vision_interface [0.26s]                                     
Starting >>> rosbag_player
Finished <<< radar_interface [0.28s]
Starting >>> tdt_vision
Starting >>> debug_map
Starting >>> dv_trigger
Starting >>> judge_bridge
Starting >>> kalman_filter
Starting >>> radar_decision
Finished <<< radar_decision [0.06s]                                
Finished <<< debug_map [0.08s]
Finished <<< rosbag_player [0.10s]
Finished <<< dv_trigger [5.09s]                                     
--- stderr: judge_bridge                                            
In file included from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/serial.hpp:3,
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/serial.cpp:1:
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/protocol.hpp:175:8: error: redefinition of ‘struct robot_interaction_sentry_data_t’
  175 | struct robot_interaction_sentry_data_t {
      |        ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/protocol.hpp:118:8: note: previous definition of ‘struct robot_interaction_sentry_data_t’
  118 | struct robot_interaction_sentry_data_t {
      |        ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/judge_bridge.hpp:15,
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:1:
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/protocol.hpp:175:8: error: redefinition of ‘struct robot_interaction_sentry_data_t’
  175 | struct robot_interaction_sentry_data_t {
      |        ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/protocol.hpp:118:8: note: previous definition of ‘struct robot_interaction_sentry_data_t’
  118 | struct robot_interaction_sentry_data_t {
      |        ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/judge_bridge.hpp:15,
                 from /home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/main.cpp:3:
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/protocol.hpp:175:8: error: redefinition of ‘struct robot_interaction_sentry_data_t’
  175 | struct robot_interaction_sentry_data_t {
      |        ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/include/judge_bridge/protocol.hpp:118:8: note: previous definition of ‘struct robot_interaction_sentry_data_t’
  118 | struct robot_interaction_sentry_data_t {
      |        ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp: In member function ‘void JudgeBridgeNode::send_sentry_data(const RadarWarn&)’:
/home/wan/SR_final_v1/SR_radar/src/judge_bridge/src/judge_bridge.cpp:206:22: error: ‘struct robot_interaction_sentry_data_t’ has no member named ‘engine_state’
  206 |     interaction_data.engine_state = topic_message.engine_state;
      |                      ^~~~~~~~~~~~
gmake[2]: *** [CMakeFiles/judge_bridge.dir/build.make:90: CMakeFiles/judge_bridge.dir/src/main.cpp.o] Error 1
gmake[2]: *** Waiting for unfinished jobs....
gmake[2]: *** [CMakeFiles/judge_bridge.dir/build.make:104: CMakeFiles/judge_bridge.dir/src/serial.cpp.o] Error 1
gmake[2]: *** [CMakeFiles/judge_bridge.dir/build.make:76: CMakeFiles/judge_bridge.dir/src/judge_bridge.cpp.o] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:137: CMakeFiles/judge_bridge.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2
---
Failed   <<< judge_bridge [5.75s, exited with code 2]
Aborted  <<< kalman_filter [9.07s]                
Aborted  <<< tdt_vision [33.8s]                                    
                                   
Summary: 9 packages finished [34.3s]
  1 package failed: judge_bridge
  2 packages aborted: kalman_filter tdt_vision
  2 packages had stderr output: judge_bridge tdt_vision
  1 package not processed
wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ 


