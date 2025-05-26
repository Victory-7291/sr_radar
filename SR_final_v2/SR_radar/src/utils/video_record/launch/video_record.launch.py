import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode
from launch.actions import Shutdown, SetEnvironmentVariable

def generate_launch_description():
    # 设置ROS2日志级别
    stdout_linebuf_envvar = SetEnvironmentVariable(
        'RCUTILS_LOGGING_BUFFERED_STREAM', '1')
        
    # 定义函数用于创建海康相机节点
    def get_hik_camera_node(package, plugin):
        params_file = os.path.join(get_package_share_directory('hik_camera'), 'config', 'camera_params.yaml')
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='hik_camera',
            parameters=[params_file],
            extra_arguments=[
                {'use_intra_process_comms': True},
                {'log_level': 'info'}
            ]
        )
    
    # 定义视频记录节点
    def get_video_record_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='video_record_node',
            remappings=[
                ('camera_image', 'camera_image')
            ],
            extra_arguments=[
                {'use_intra_process_comms': True},
                {'log_level': 'info'}
            ]
        )
    
    # 创建节点容器函数
    def get_camera_recorder_container(nodes):
        return ComposableNodeContainer(
            name='camera_recorder_container',
            namespace='',
            package='rclcpp_components',
            executable='component_container',
            composable_node_descriptions=nodes,
            output='both',
            arguments=['--ros-args', '--log-level', 'info'],
            emulate_tty=True,
            on_exit=Shutdown(),
        )
    
    # 创建节点描述
    hik_camera_node = get_hik_camera_node('ros2_hik_camera', 'hik_camera::HikCameraNode')
    video_record_node = get_video_record_node('video_record', 'video_record::VideoRecordNode')
    
    # 创建节点容器，确保hik_camera_node是第一个
    nodes = [
        hik_camera_node,
        video_record_node
    ]
    
    # 获取容器
    camera_recorder = get_camera_recorder_container(nodes)
    
    return LaunchDescription([
        stdout_linebuf_envvar,
        camera_recorder
    ]) 