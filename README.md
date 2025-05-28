wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ colcon build
Starting >>> radar_interface
Starting >>> vision_interface
Starting >>> hik_camera
Starting >>> libocsort
Starting >>> video_player
Starting >>> video_recorder
Finished <<< hik_camera [0.44s]                                           
Finished <<< libocsort [0.44s]
Finished <<< video_recorder [0.46s]
Finished <<< vision_interface [0.67s]                                  
Starting >>> rosbag_player
Finished <<< radar_interface [0.69s]
Starting >>> tdt_vision
Starting >>> debug_map
Starting >>> dv_trigger
Starting >>> judge_bridge
Starting >>> kalman_filter
Starting >>> radar_decision
Finished <<< radar_decision [0.08s]                               
Finished <<< dv_trigger [0.09s]
Finished <<< rosbag_player [0.12s]
Finished <<< debug_map [0.11s]                                    
Finished <<< judge_bridge [0.12s]
Finished <<< kalman_filter [0.13s]
--- stderr: video_player                                               
/home/wan/SR_final_v1/SR_radar/src/utils/video_player/src/video_player_node.cpp: In member function ‘void video_player::VideoPlayerNode::timer_callback()’:
/home/wan/SR_final_v1/SR_radar/src/utils/video_player/src/video_player_node.cpp:146:35: error: ‘fps’ was not declared in this scope; did you mean ‘ffs’?
  146 |     double frame_interval = 1.0 / fps;
      |                                   ^~~
      |                                   ffs
gmake[2]: *** [CMakeFiles/video_player.dir/build.make:76: CMakeFiles/video_player.dir/src/video_player_node.cpp.o] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:139: CMakeFiles/video_player.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2
---
Failed   <<< video_player [3.64s, exited with code 2]
Aborted  <<< tdt_vision [10.4s]                                    

Summary: 11 packages finished [11.5s]
  1 package failed: video_player
  1 package aborted: tdt_vision
  2 packages had stderr output: tdt_vision video_player
  1 package not processed
wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ 


