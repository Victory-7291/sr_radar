# sr_radar

wan@wan-Predator-PHN16-71:~/SR$ colcon build
Starting >>> vision_interface
Starting >>> livox_interfaces
Starting >>> livox_sdk_vendor
Starting >>> radar_interface
Starting >>> cluster
Starting >>> hik_camera
Starting >>> localization
Finished <<< livox_sdk_vendor [0.52s]                                 
Finished <<< livox_interfaces [3.87s]                                     
Starting >>> livox_ros2_driver
Finished <<< vision_interface [5.54s]                                      
Starting >>> debug_map
Starting >>> dynamic_cloud
Starting >>> kalman_filter
Starting >>> rosbag_player
Starting >>> tdt_vision
Finished <<< hik_camera [6.78s]                                           
--- stderr: debug_map                                                    
/home/wan/SR/SR_radar/src/fusion/debug_map/debug_map.cpp:13:10: fatal error: radar_interface/msg/match_result.hpp: No such file or directory
   13 | #include <radar_interface/msg/match_result.hpp>
      |          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
gmake[2]: *** [CMakeFiles/debug_map.dir/build.make:76: CMakeFiles/debug_map.dir/debug_map.cpp.o] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:137: CMakeFiles/debug_map.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2

---

Failed   <<< debug_map [1.35s, exited with code 2]
Aborted  <<< livox_ros2_driver [3.56s]           
Aborted  <<< kalman_filter [2.38s]               
Aborted  <<< dynamic_cloud [2.47s]
Aborted  <<< rosbag_player [2.50s]               
Aborted  <<< radar_interface [8.49s]             
Aborted  <<< tdt_vision [3.91s]                                              
Aborted  <<< cluster [13.6s]                                                    
Aborted  <<< localization [20.8s]                                    

Summary: 4 packages finished [21.0s]
  1 package failed: debug_map
  8 packages aborted: cluster dynamic_cloud kalman_filter livox_ros2_driver localization radar_interface rosbag_player tdt_vision
  3 packages had stderr output: debug_map livox_ros2_driver tdt_vision
  1 package not processed
