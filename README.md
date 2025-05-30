wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ ros2 launch tdt_vision calib_video.launch.py 
[INFO] [launch]: All log files can be found below /home/wan/.ros/log/2025-05-30-14-25-06-009230-wan-Predator-PHN16-71-157551
[INFO] [launch]: Default logging verbosity is set to INFO
[INFO] [component_container-1]: process started with pid [157563]
[component_container-1] [INFO] [1748586306.321910051] [camera_detector_container]: Load Library: /home/wan/SR_final_v1/SR_radar/install/video_streamer_cpp/lib/libvideo_streamer_cpp.so
[component_container-1] [INFO] [1748586306.456294718] [camera_detector_container]: Found class: rclcpp_components::NodeFactoryTemplate<video_streamer_cpp::VideoStreamerNode>
[component_container-1] [INFO] [1748586306.456367279] [camera_detector_container]: Instantiate class: rclcpp_components::NodeFactoryTemplate<video_streamer_cpp::VideoStreamerNode>
[component_container-1] [INFO] [1748586306.460925647] [video_streamer_cpp_node]: VideoStreamerNode component created.
[component_container-1] [INFO] [1748586306.461199399] [video_streamer_cpp_node]: Parameters: video_file_path='/home/wan/radar_video/video_recording_20250528_091342.mp4', output_topic='/video_image', loop=1, target_fps=120.00, force_fps=0
[component_container-1] [INFO] [1748586306.461234944] [video_streamer_cpp_node]: Opening video file: /home/wan/radar_video/video_recording_20250528_091342.mp4
[component_container-1] [INFO] [1748586306.472290261] [video_streamer_cpp_node]: Video file opened successfully. Width: 3072, Height: 2048
[component_container-1] [INFO] [1748586306.474883644] [video_streamer_cpp_node]: Video FPS: 60.00. Using this as publishing rate.
[INFO] [launch_ros.actions.load_composable_nodes]: Loaded node '/video_streamer_cpp_node' in container '/camera_detector_container'
[component_container-1] [INFO] [1748586306.474926785] [video_streamer_cpp_node]: Publishing at 60.00 FPS, with frame interval: 0.0167 seconds.
[component_container-1] [INFO] [1748586306.475101467] [video_streamer_cpp_node]: VideoStreamerNode initialized, publishing video to '/video_image' at 60.00 FPS.
^C[WARNING] [launch]: user interrupted with ctrl-c (SIGINT)
[component_container-1] [INFO] [1748586327.711379221] [rclcpp]: signal_handler(signum=2)
[component_container-1] [INFO] [1748586327.727278292] [video_streamer_cpp_node]: VideoStreamerNode component destroyed.
[INFO] [component_container-1]: process has finished cleanly [pid 157563]
[INFO] [launch]: process[component_container-1] was required: shutting down launched system
[ERROR] [launch]: Caught exception in launch (see debug for traceback): Cannot shutdown a ROS adapter that is not running
wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ 


