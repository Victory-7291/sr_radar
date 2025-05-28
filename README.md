wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ colcon build
Starting >>> radar_interface
Starting >>> vision_interface
Starting >>> hik_camera
Starting >>> libocsort
Starting >>> video_player
Starting >>> video_recorder
Finished <<< libocsort [0.14s]                                           
Finished <<< video_recorder [0.16s]
Finished <<< hik_camera [0.18s]
Finished <<< radar_interface [0.41s]                                      
Starting >>> dv_trigger
Starting >>> radar_decision
Finished <<< vision_interface [0.41s]
Starting >>> tdt_vision
Starting >>> debug_map
Starting >>> judge_bridge
Starting >>> kalman_filter
Starting >>> rosbag_player
Finished <<< radar_decision [0.09s]
Finished <<< dv_trigger [0.13s]                                   
Finished <<< debug_map [0.12s]
Finished <<< rosbag_player [0.15s]
Finished <<< judge_bridge [0.16s]
Finished <<< kalman_filter [0.17s]
--- stderr: video_player                                                
/usr/bin/ld: /usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/Scrt1.o: in function `_start':
(.text+0x1b): undefined reference to `main'
collect2: error: ld returned 1 exit status
gmake[2]: *** [CMakeFiles/video_player_node.dir/build.make:243: video_player_node] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:165: CMakeFiles/video_player_node.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2
---
Failed   <<< video_player [5.28s, exited with code 2]
Aborted  <<< tdt_vision [10.8s]                                   
                                   
Summary: 11 packages finished [11.4s]
  1 package failed: video_player
  1 package aborted: tdt_vision
  2 packages had stderr output: tdt_vision video_player
  1 package not processed
wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ 

