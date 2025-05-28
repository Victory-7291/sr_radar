
## 测试
    
```bash
ros2 launch tdt_vision run_rosbag.launch.py #通过rosbag启动相机
ros2 launch dynamic_cloud lidar.launch.py #启动激光雷达识别
ros2 run debug_map debug_map #启动地图可视化
ros2 launch livox_ros2_driver livox_lidar_launch.py #启动Livox驱动
```
测试ros2bag下载
[百度网盘](https://pan.baidu.com/s/1ogRvs3v1OMCVUbAlUsOGQA?pwd=52rm)

修改tdt_vision/launch对应的launch文件中的rosbag路径即可进程内播放对应的rosbag
### 相机外参标定
```bash
ros2 run tdt_vision calib_rosbag.launch.py
chmod +x /Users/wan/Documents/SR_final_v1/record_topics.py
```

</div>
