import os
import sys
from ament_index_python.packages import get_package_share_directory

sys.path.append(os.path.join(get_package_share_directory('tdt_vision'), 'launch'))

from launch_ros.descriptions import ComposableNode
from launch_ros.actions import ComposableNodeContainer, Node
from launch.actions import TimerAction, Shutdown
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    # 定义rosbag文件路径参数
    rosbag_file_arg = DeclareLaunchArgument(
        'rosbag_file',
        default_value='/home/wan/Documents/SR_final_v1/SR_radar/radar_data_20250530_162124/radar_data_20250530_162124_0.db3',
        description='Path to the rosbag file (.db3)'
    )
    
    # 添加时间戳和播放速率参数
    use_original_timestamps_arg = DeclareLaunchArgument(
        'use_original_timestamps',
        default_value='true',
        description='Use original timestamps from rosbag file'
    )
    
    playback_rate_arg = DeclareLaunchArgument(
        'playback_rate',
        default_value='1.0',
        description='Playback rate multiplier (1.0 = normal speed)'
    )

    # 定义RosbagPlayer节点
    def get_rosbag_player_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='rosbag_player_node',
            parameters=[{
                'rosbag_file': LaunchConfiguration('rosbag_file'),
                'use_original_timestamps': LaunchConfiguration('use_original_timestamps'),
                'playback_rate': LaunchConfiguration('playback_rate')
            }],
            extra_arguments=[{'use_intra_process_comms': True}]
        )

    # 定义RadarWarn节点
    radar_warn_node = Node(
        package='radar_warn',
        executable='radar_warn_node',
        name='radar_warn_node',
        output='screen'
    )

    # 定义 dv_trigger 节点
    dv_trigger_node = Node(
        package='dv_trigger',
        executable='dv_trigger',
        name='dv_trigger_node',
        output='screen'
    )

    def get_radar_detect_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='radar_detect_node',
            extra_arguments=[{'use_intra_process_comms': True}]
        )

    def get_radar_resolve_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='radar_resolve_node',
            extra_arguments=[{'use_intra_process_comms': True}]
        )

    def get_foxglove_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='foxglove_bridge_node',
            parameters=[{'send_buffer_limit': 1000000000}],
            extra_arguments=[{'use_intra_process_comms': True},
                             {'use_multi_threaded_executor': True}]
        )

    def get_kalman_filter_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='kalman_filter_node',
            extra_arguments=[{'use_intra_process_comms': True}]
        )

    def get_container(nodes):
        return ComposableNodeContainer(
            name='rosbag_container',
            namespace='',
            package='rclcpp_components',
            executable='component_container',
            composable_node_descriptions=nodes,
            output='both',
            emulate_tty=True,
            on_exit=Shutdown(),
        )

    # 创建节点描述
    rosbag_player_node = get_rosbag_player_node('rosbag_player', 'RosbagPlayer')
    radar_detect_node = get_radar_detect_node('tdt_vision', 'tdt_radar::Detect')
    radar_resolve_node = get_radar_resolve_node('tdt_vision', 'tdt_radar::Resolve')
    foxglove_node = get_foxglove_node('foxglove_bridge', 'foxglove_bridge::FoxgloveBridge')
    kalman_filter_node = get_kalman_filter_node('kalman_filter', 'tdt_radar::KalmanFilter')

    # 创建节点容器
    nodes = [
        rosbag_player_node,
        radar_detect_node,
        radar_resolve_node,
        foxglove_node,
        kalman_filter_node
    ]
    
    container = get_container(nodes)

    return LaunchDescription([
        rosbag_file_arg,
        use_original_timestamps_arg,
        playback_rate_arg,
        dv_trigger_node,
        radar_warn_node,
        container
    ]) 