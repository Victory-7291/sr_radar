wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ colcon build
Starting >>> radar_interface
Starting >>> vision_interface
Starting >>> hik_camera
Starting >>> libocsort
Starting >>> video_player
Starting >>> video_recorder
Starting >>> video_streamer_cpp
Finished <<< libocsort [0.10s]                                           
Finished <<< hik_camera [0.11s]
Finished <<< video_recorder [0.13s]
Finished <<< video_player [0.14s]
Finished <<< video_streamer_cpp [0.15s]
Finished <<< radar_interface [0.28s]                                      
Starting >>> dv_trigger
Starting >>> radar_decision
Finished <<< vision_interface [0.30s]                                   
Starting >>> tdt_vision
Starting >>> debug_map
Starting >>> judge_bridge
Starting >>> kalman_filter
Starting >>> rosbag_player
Finished <<< radar_decision [0.08s]
Finished <<< dv_trigger [0.11s]
Finished <<< debug_map [0.11s]                                      
Finished <<< kalman_filter [0.13s]
--- stderr: rosbag_player                                            
/home/wan/SR_final_v1/SR_radar/src/utils/rosbag_player/rosbag_player.cpp:7:10: fatal error: std_msgs/msg/uint16.hpp: No such file or directory
    7 | #include <std_msgs/msg/uint16.hpp>
      |          ^~~~~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
gmake[2]: *** [CMakeFiles/rosbag_player.dir/build.make:76: CMakeFiles/rosbag_player.dir/rosbag_player.cpp.o] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:139: CMakeFiles/rosbag_player.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2
---
Failed   <<< rosbag_player [0.26s, exited with code 2]
Aborted  <<< judge_bridge [11.2s]                  
Aborted  <<< tdt_vision [11.2s]                                   

Summary: 11 packages finished [11.7s]
  1 package failed: rosbag_player
  2 packages aborted: judge_bridge tdt_vision
  2 packages had stderr output: rosbag_player tdt_vision
  1 package not processed

