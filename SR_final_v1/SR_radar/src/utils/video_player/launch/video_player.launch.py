import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    # 声明参数（全部为可选）
    video_file_path_arg = DeclareLaunchArgument(
        'video_file_path',
        default_value='',
        description='Path to the video file to play (optional, defaults to value in code)'
    )
    
    use_camera_arg = DeclareLaunchArgument(
        'use_camera',
        default_value='false',
        description='Whether to use camera instead of video file (optional)'
    )
    
    camera_id_arg = DeclareLaunchArgument(
        'camera_id',
        default_value='0',
        description='Camera ID to use if use_camera is true (optional)'
    )
    
    loop_arg = DeclareLaunchArgument(
        'loop',
        default_value='true',
        description='Whether to loop video playback (optional)'
    )
    
    frame_rate_arg = DeclareLaunchArgument(
        'frame_rate',
        default_value='30.0',
        description='Default frame rate to use if cannot be determined from video (optional)'
    )
    
    force_frame_rate_arg = DeclareLaunchArgument(
        'force_frame_rate',
        default_value='false',
        description='Whether to force using the specified frame rate instead of the video file frame rate (optional)'
    )

    # 创建节点
    video_player_node = Node(
        package='video_player',
        executable='video_player_node',
        name='video_player',
        output='screen',
        parameters=[{
            'video_file_path': LaunchConfiguration('video_file_path'),
            'use_camera': LaunchConfiguration('use_camera'),
            'camera_id': LaunchConfiguration('camera_id'),
            'loop': LaunchConfiguration('loop'),
            'frame_rate': LaunchConfiguration('frame_rate'),
            'force_frame_rate': LaunchConfiguration('force_frame_rate')
        }]
    )

    return LaunchDescription([
        video_file_path_arg,
        use_camera_arg,
        camera_id_arg,
        loop_arg,
        frame_rate_arg,
        force_frame_rate_arg,
        video_player_node
    ]) 