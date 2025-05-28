wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ ros2 launch video_player video_player.launch.py 
[INFO] [launch]: All log files can be found below /home/wan/.ros/log/2025-05-28-19-06-23-518819-wan-Predator-PHN16-71-9746
[INFO] [launch]: Default logging verbosity is set to INFO
[INFO] [video_player_node-1]: process started with pid [9747]
[video_player_node-1] [INFO] [1748430383.681571670] [video_player]: VideoPlayerNode created
[video_player_node-1] [ERROR] [1748430383.681925111] [video_player]: Video file path is not set.
[video_player_node-1] terminate called after throwing an instance of 'std::runtime_error'
[video_player_node-1]   what():  Video file path is not set.
[ERROR] [video_player_node-1]: process has died [pid 9747, exit code -6, cmd '/home/wan/SR_final_v1/SR_radar/install/video_player/lib/video_player/video_player_node --ros-args -r __node:=video_player --params-file /tmp/launch_params_a7pkt82y'].
wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ ros2 launch video_player video_player.launch.py --ros-args -p video_file_path:=/home/wan/radar_video/video_recording_20250528_091342.mp4
usage: ros2 [-h] [--use-python-default-buffering] Call `ros2 <command> -h` for more detailed usage. ...
ros2: error: unrecognized arguments: --ros-args video_file_path:=/home/wan/radar_video/video_recording_20250528_091342.mp4
wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ 


