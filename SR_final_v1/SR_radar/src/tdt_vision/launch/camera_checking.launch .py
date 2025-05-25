import os
import sys
import yaml
from ament_index_python.packages import get_package_share_directory

sys.path.append(os.path.join(get_package_share_directory('tdt_vision'), 'launch'))

from launch_ros.descriptions import ComposableNode
from launch_ros.actions import ComposableNodeContainer, Node
from launch.actions import TimerAction, Shutdown, SetEnvironmentVariable
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    # 设置ROS2日志级别
    stdout_linebuf_envvar = SetEnvironmentVariable(
        'RCUTILS_LOGGING_BUFFERED_STREAM', '1')
           
    # 定义节点
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

    def get_camera_detector_container(nodes):
        return ComposableNodeContainer(
            name='camera_detector_container',
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
    hik_camera_node = get_hik_camera_node('hik_camera', 'hik_camera::HikCameraNode')

    # 创建节点容器，确保 hik_camera_node 是第一个
    nodes = [
        hik_camera_node,  
    ]
    cam_detector = get_camera_detector_container(nodes)

    return LaunchDescription([
        stdout_linebuf_envvar,
        cam_detector,
    ])
