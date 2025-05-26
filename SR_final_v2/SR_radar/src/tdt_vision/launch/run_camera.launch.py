import os
import sys
import yaml
from ament_index_python.packages import get_package_share_directory

sys.path.append(os.path.join(get_package_share_directory('tdt_vision'), 'launch'))

from launch_ros.descriptions import ComposableNode
from launch_ros.actions import ComposableNodeContainer, Node
from launch.actions import TimerAction, Shutdown, SetEnvironmentVariable
from launch import LaunchDescription

from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # 设置ROS2日志级别
    stdout_linebuf_envvar = SetEnvironmentVariable(
        'RCUTILS_LOGGING_BUFFERED_STREAM', '1')

    # 定义JudgeBridgeNode节点
    judge_bridge_node = Node(
        package='judge_bridge',
        executable='judge_bridge',
        name='judge_bridge_node',
        output='screen',
        arguments=['--ros-args', '--log-level', 'info'],
        emulate_tty=True,
        parameters=[{
            'serial_port': '/dev/ttyUSB0',
            'enable_recorder': False
        }]
    )

    # 定义RadarWarn节点
    radar_warn_node = Node(
        package='radar_warn',
        executable='radar_warn_node',
        name='radar_warn_node',
        output='screen',
        arguments=['--ros-args', '--log-level', 'info'],
        emulate_tty=True
    )

    # 定义节点
    def get_rosbag_player_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='rosbag_player_node',
            parameters=[{
                'rosbag_file': '/home/wan/rosbag_test/merged_bag_0.db3'
            }],
            extra_arguments=[
                {'use_intra_process_comms': True},
                {'log_level': 'info'}
            ]
        )

    def get_foxglove_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='foxglove_bridge_node',
            parameters=[{'send_buffer_limit': 1000000000}],
            extra_arguments=[
                {'use_intra_process_comms': True},
                {'use_multi_threaded_executor': True},
                {'log_level': 'info'}
            ]
        )

    def get_radar_detect_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='radar_detect_node',
            extra_arguments=[
                {'use_intra_process_comms': True},
                {'log_level': 'info'}
            ]
        )

    def get_radar_resolve_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='radar_resolve_node',
            extra_arguments=[
                {'use_intra_process_comms': True},
                {'log_level': 'info'}
            ]
        )
    
    def get_kalman_filter_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='kalman_filter_node',
            extra_arguments=[
                {'use_intra_process_comms': True},
                {'log_level': 'info'}
            ]
        )

    #def get_hik_camera_node(package, plugin):
    #    return ComposableNode(
    #        package=package,
    #        plugin=plugin,
    #        name='hik_camera',
    #        parameters=[LaunchConfiguration('params_file'), {
    #            'camera_info_url': LaunchConfiguration('camera_info_url'),
    #            'use_sensor_data_qos': LaunchConfiguration('use_sensor_data_qos'),
    #        }],
    #        extra_arguments=[{'use_intra_process_comms': True}]
    #    )
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
    radar_detect_node = get_radar_detect_node('tdt_vision', 'tdt_radar::Detect')
    radar_resolve_node = get_radar_resolve_node('tdt_vision', 'tdt_radar::Resolve')
    foxglove_node = get_foxglove_node('foxglove_bridge', 'foxglove_bridge::FoxgloveBridge')
    rosbag_player_node = get_rosbag_player_node('rosbag_player', 'RosbagPlayer')
    kalman_filter_node = get_kalman_filter_node('kalman_filter', 'tdt_radar::KalmanFilter')

    # 定义 dv_trigger 节点
    dv_trigger_node = Node(
        package='dv_trigger',
        executable='dv_trigger', # 假设可执行文件名为 dv_trigger_node
        name='dv_trigger_node',
        output='screen',
        arguments=['--ros-args', '--log-level', 'info'],
        emulate_tty=True
    )

    # 创建节点容器，确保 hik_camera_node 是第一个
    nodes = [
        hik_camera_node,
        radar_detect_node,
        radar_resolve_node,
        foxglove_node,
        rosbag_player_node,
        kalman_filter_node
    ]
    cam_detector = get_camera_detector_container(nodes)

    # 包含 map_server_launch.py
    #plugin_map_launch_cmd = IncludeLaunchDescription(
    #    PythonLaunchDescriptionSource([os.path.join(
    #        get_package_share_directory('tdt_vision'), 'launch', 'map_server_launch.py')]),
    #)

    return LaunchDescription([
        stdout_linebuf_envvar,
        # 首先启动JudgeBridgeNode节点
        judge_bridge_node,
        radar_warn_node,  # 添加radar_warn节点
        dv_trigger_node,  # 添加 dv_trigger 节点到启动列表
        cam_detector,
        #plugin_map_launch_cmd,
    ])
