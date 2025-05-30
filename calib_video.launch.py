import os
import sys
import yaml
from ament_index_python.packages import get_package_share_directory

sys.path.append(os.path.join(get_package_share_directory('tdt_vision'), 'launch'))

from launch_ros.descriptions import ComposableNode
from launch_ros.actions import ComposableNodeContainer, Node
from launch.actions import TimerAction, Shutdown
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

    # --- C++ VideoStreamerComponent 参数 ---
    video_file_path_arg_cpp = DeclareLaunchArgument(
        'video_file_path_cpp',
        default_value='/home/wan/radar_video/video_recording_20250528_091342.mp4',
        description='Path to the video file for C++ VideoStreamerNode.'
    )
    video_output_topic_arg_cpp = DeclareLaunchArgument(
        'video_output_topic_cpp',
        default_value='/video_image',
        description='Topic name for images published by C++ VideoStreamerNode.'
    )
    video_streamer_loop_arg = DeclareLaunchArgument(
        'video_streamer_loop',
        default_value='True',
        description='Loop video for C++ VideoStreamerNode.'
    )
    video_streamer_target_fps_arg = DeclareLaunchArgument(
        'video_streamer_target_fps',
        default_value='120.0',
        description='Target publishing FPS for C++ VideoStreamerNode.'
    )
    video_streamer_force_fps_arg = DeclareLaunchArgument(
        'video_streamer_force_fps',
        default_value='False',
        description='Force target_fps for C++ VideoStreamerNode, ignoring video file FPS.'
    )

    def get_hik_camera_node(package, plugin):
        params_file = os.path.join(get_package_share_directory('hik_camera'), 'config', 'camera_params.yaml')
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='hik_camera',
            parameters=[params_file],
            extra_arguments=[{'use_intra_process_comms': True}]
        )

        
    #def get_rosbag_player_node(package, plugin):
    #    return ComposableNode(
    #        package=package,
    #        plugin=plugin,
    #        name='rosbag_player_node',
    #        parameters=[ {'rosbag_file': 
    #            '/home/wan/rosbag_test/merged_bag_0.db3'
    #            #'/home/shenxw/Rosbag/适应性录像第二把/merged_bag/merged_bag_0.db3'
    #            }],
    #        extra_arguments=[{'use_intra_process_comms': True}]
    #    )  

  
    #def get_video_player_node(package, plugin):
    #    # 使用相对于工作空间的路径
    #    workspace_path = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
    #    video_path = os.path.join(workspace_path, 'test.mp4')
    #    
    #    return ComposableNode(
    #        package=package,
    #        plugin=plugin,
    #        name='video_player_node',
    #        parameters=[{'video_file_path': video_path}],
    #        extra_arguments=[{'use_intra_process_comms': True}]
    #    )

    def get_radar_calib_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='radar_calib_node',
            extra_arguments=[{'use_intra_process_comms': True}]
        )

    # 定义video_streamer_cpp节点
    def get_video_streamer_cpp_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='video_streamer_cpp_node',
            parameters=[{
                'video_file_path': LaunchConfiguration('video_file_path_cpp'),
                'output_topic': LaunchConfiguration('video_output_topic_cpp'),
                'loop': LaunchConfiguration('video_streamer_loop'),
                'target_fps': LaunchConfiguration('video_streamer_target_fps'),
                'force_fps': LaunchConfiguration('video_streamer_force_fps'),
            }],
            extra_arguments=[{'use_intra_process_comms': True}]
        )

    def get_camera_detector_container(hik_camera_node, radar_calib_node, video_streamer_cpp_node=None):
        nodes = []
        if video_streamer_cpp_node:
            nodes.append(video_streamer_cpp_node)
        # 添加其他节点
        nodes.extend([radar_calib_node])
        
        return ComposableNodeContainer(
            name='camera_detector_container',
            namespace='',
            package='rclcpp_components',
            executable='component_container',
            composable_node_descriptions=nodes,
            output='both',
            emulate_tty=True,
            on_exit=Shutdown(),
        )
    # 创建节点描述
    hik_camera_node = get_hik_camera_node('hik_camera', 'hik_camera::HikCameraNode')
    radar_calib_node = get_radar_calib_node('tdt_vision', 'tdt_radar::Calibrate')
    video_streamer_cpp_node = get_video_streamer_cpp_node('video_streamer_cpp', 'video_streamer_cpp::VideoStreamerNode')
    #video_player_node = get_video_player_node('video_player', 'video_player::VideoPlayerNode') # 包名和插件名已更正
    #ros_bag_player_node = get_rosbag_player_node('rosbag_player', 'RosbagPlayer')

    # 创建节点容器
    cam_detector = get_camera_detector_container(
        hik_camera_node,
        radar_calib_node,
        video_streamer_cpp_node
        #video_player_node,
        #ros_bag_player_node

    )
    #debug_container = get_debug_container(tdt_debug_node)
    #plugin_map_launch_cmd = IncludeLaunchDescription(
    #            PythonLaunchDescriptionSource([os.path.join(
    #                get_package_share_directory('tdt_vision'), 'launch', 'map_server_launch.py')]),
    #         )
    return LaunchDescription([
            # 添加视频流参数
            video_file_path_arg_cpp,
            video_output_topic_arg_cpp,
            video_streamer_loop_arg,
            video_streamer_target_fps_arg,
            video_streamer_force_fps_arg,
            # 节点容器
            cam_detector,
            #plugin_map_launch_cmd
        ])
