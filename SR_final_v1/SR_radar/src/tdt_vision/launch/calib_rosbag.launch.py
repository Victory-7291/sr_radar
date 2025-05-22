import os
import sys
import yaml
from ament_index_python.packages import get_package_share_directory

sys.path.append(os.path.join(get_package_share_directory('tdt_vision'), 'launch'))

from launch_ros.descriptions import ComposableNode
from launch_ros.actions import ComposableNodeContainer, Node
from launch.actions import TimerAction, Shutdown
from launch import LaunchDescription

from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # 定义视频和rosbag路径
    workspace_path = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
    video_path = os.path.join(workspace_path, 'test.mp4')
    rosbag_path = os.path.join(workspace_path, 'test_video_bag')
    
    # 视频播放器节点 - 使用rosbag作为源
    def get_video_player_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='video_player_node',
            parameters=[{
                'source_type': 'rosbag',
                'rosbag_file_path': rosbag_path,
                'rosbag_topic': '/video_image',
                'topic_name': 'video_image',
                'loop': True,
                'frame_rate': 30.0
            }],
            extra_arguments=[{'use_intra_process_comms': True}]
        )

    def get_radar_calib_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='radar_calib_node',
            extra_arguments=[{'use_intra_process_comms': True}]
        )

    def get_camera_detector_container(radar_calib_node, video_player_node,):
        return ComposableNodeContainer(
            name='camera_detector_container',
            namespace='',
            package='rclcpp_components',
            executable='component_container',
            composable_node_descriptions=[
                #变向设置启动顺序
                #hik_camera_node,
                radar_calib_node,
                video_player_node,
                #ros_bag_player_node
            ],
            output='both',
            emulate_tty=True,
            on_exit=Shutdown(),
        )
    # 创建节点描述
    #hik_camera_node = get_hik_camera_node('hik_camera', 'hik_camera::HikCameraNode')
    radar_calib_node = get_radar_calib_node('tdt_vision', 'tdt_radar::Calibrate')
    video_player_node = get_video_player_node('video_player', 'video_player::VideoPlayerNode') # 包名和插件名已更正
    #ros_bag_player_node = get_rosbag_player_node('rosbag_player', 'RosbagPlayer')

    # 创建节点容器
    cam_detector = get_camera_detector_container(
        #hik_camera_node,
        radar_calib_node,
        video_player_node,
        #ros_bag_player_node
    )
    
    return LaunchDescription([
            cam_detector,
        ])
