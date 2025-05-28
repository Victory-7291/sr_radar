import os
import sys
import yaml
from ament_index_python.packages import get_package_share_directory

sys.path.append(os.path.join(get_package_share_directory('tdt_vision'), 'launch'))

from launch_ros.descriptions import ComposableNode
from launch_ros.actions import ComposableNodeContainer, Node
from launch.actions import TimerAction, Shutdown
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():

    # --- mp42ros (Python) 节点参数 - 保留以供参考或独立使用 ---
    # video_file_path_arg_py = DeclareLaunchArgument(
    #     'video_file_path_py',
    #     default_value='/home/wan/radar_video/video_recording_20250528_091342.mp4',
    #     description='Path to the mp4 video file for Python mp42ros node.'
    # )
    # video_output_topic_arg_py = DeclareLaunchArgument(
    #     'video_output_topic_py',
    #     default_value='/image_raw_py',
    #     description='Topic name for images published by Python mp42ros node.'
    # )
    # mp42ros_loop_arg_py = DeclareLaunchArgument(
    #     'mp42ros_loop_py',
    #     default_value='True',
    #     description='Loop video for Python mp42ros node.'
    # )
    # mp42ros_fps_arg_py = DeclareLaunchArgument(
    #     'mp42ros_fps_py',
    #     default_value='15.0',
    #     description='Publishing FPS for Python mp42ros node.'
    # )
    # mp42ros_node_py = Node(
    #     package='mp42ros',
    #     executable='runner',
    #     name='mp42ros_publisher_py',
    #     output='screen',
    #     parameters=[{
    #         'mp4_file_path': LaunchConfiguration('video_file_path_py'),
    #         'send_topic_name': LaunchConfiguration('video_output_topic_py'),
    #         'loop': LaunchConfiguration('mp42ros_loop_py'),
    #         'fps': LaunchConfiguration('mp42ros_fps_py'),
    #     }]
    # )

    # --- C++ VideoStreamerComponent 参数 ---
    video_file_path_arg_cpp = DeclareLaunchArgument(
        'video_file_path_cpp',
        default_value='/home/wan/radar_video/video_recording_20250528_091342.mp4', # 请务必修改为您的实际视频路径
        description='Path to the video file for C++ VideoStreamerNode.'
    )
    video_output_topic_arg_cpp = DeclareLaunchArgument(
        'video_output_topic_cpp',
        default_value='/video_image', # C++ 组件发布图像的话题
        description='Topic name for images published by C++ VideoStreamerNode.'
    )
    video_streamer_loop_arg = DeclareLaunchArgument(
        'video_streamer_loop',
        default_value='True',
        description='Loop video for C++ VideoStreamerNode.'
    )
    video_streamer_target_fps_arg = DeclareLaunchArgument(
        'video_streamer_target_fps',
        default_value='60.0',
        description='Target publishing FPS for C++ VideoStreamerNode.'
    )
    video_streamer_force_fps_arg = DeclareLaunchArgument(
        'video_streamer_force_fps',
        default_value='False',
        description='Force target_fps for C++ VideoStreamerNode, ignoring video file FPS.'
    )

    # 定义JudgeBridgeNode节点
    judge_bridge_node = Node(
        package='judge_bridge',
        executable='judge_bridge',
        name='judge_bridge_node',
        output='screen',
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
        output='screen'
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

    def get_radar_detect_node(package, plugin):
        # 假设 radar_detect_node 订阅 video_output_topic_cpp 定义的话题
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='radar_detect_node',
            # remappings=[('/input/image', LaunchConfiguration('video_output_topic_cpp'))], # 取消注释并根据需要调整
            extra_arguments=[{'use_intra_process_comms': True}]
        )

    def get_radar_resolve_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='radar_resolve_node',
            extra_arguments=[{'use_intra_process_comms': True}]
        )
    
    def get_debug_map_node(package, plugin):
        return ComposableNode(
            package=package,
            plugin=plugin,
            name='debug_map_node',
            extra_arguments=[{'use_intra_process_comms': True}]
        )

    #def get_kalman_filter_node(package, plugin):
    #    return ComposableNode(
    #        package=package,
    #        plugin=plugin,
    #        name='kalman_filter_node',
    #        extra_arguments=[{'use_intra_process_comms': True}]
    #    )
        
    # 定义新的 C++ VideoStreamerNode 组件
    video_streamer_cpp_node = ComposableNode(
        package='video_streamer_cpp',
        plugin='video_streamer_cpp::VideoStreamerNode',
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

    # 定义 dv_trigger 节点
    dv_trigger_node = Node(
        package='dv_trigger',
        executable='dv_trigger',
        name='dv_trigger_node',
        output='screen'
    )

    def get_camera_detector_container(nodes):
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
    radar_detect_node = get_radar_detect_node('tdt_vision', 'tdt_radar::Detect')
    radar_resolve_node = get_radar_resolve_node('tdt_vision', 'tdt_radar::Resolve')
    foxglove_node = get_foxglove_node('foxglove_bridge', 'foxglove_bridge::FoxgloveBridge')
    debug_map_node = get_debug_map_node('debug_map', 'tdt_radar::DebugMap')
    #kalman_filter_node = get_kalman_filter_node('kalman_filter', 'tdt_radar::KalmanFilter')

    # 创建节点容器，将 video_streamer_cpp_node 添加到列表中
    nodes_in_container = [
        video_streamer_cpp_node, # C++ 视频流组件
        radar_detect_node,
        radar_resolve_node,
        foxglove_node,
        debug_map_node,
        #kalman_filter_node
    ]
    cam_detector_container = get_camera_detector_container(nodes_in_container)

    return LaunchDescription([
        # C++ VideoStreamerComponent 的启动参数声明
        video_file_path_arg_cpp,
        video_output_topic_arg_cpp,
        video_streamer_loop_arg,
        video_streamer_target_fps_arg,
        video_streamer_force_fps_arg,

        # # Python mp42ros 节点的启动参数和节点 (注释掉，因为我们用C++组件替代)
        # video_file_path_arg_py,
        # video_output_topic_arg_py,
        # mp42ros_loop_arg_py,
        # mp42ros_fps_arg_py,
        # mp42ros_node_py,
        
        judge_bridge_node,
        dv_trigger_node,
        radar_warn_node,
        cam_detector_container, # 包含 C++ 视频组件和其他处理组件的容器
    ])
