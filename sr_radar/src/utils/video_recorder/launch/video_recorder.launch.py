from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'output_dir',
            default_value='/home/wan/radar_video',
            description='视频文件保存目录路径'
        ),
        DeclareLaunchArgument(
            'filename_prefix',
            default_value='video_recording',
            description='视频文件名前缀'
        ),
        DeclareLaunchArgument(
            'fps',
            default_value='60.0',
            description='视频帧率'
        ),
        DeclareLaunchArgument(
            'fourcc',
            default_value='mp4v',
            description='视频编码格式（FourCC码）'
        ),
        DeclareLaunchArgument(
            'topic',
            default_value='/camera_image',
            description='要订阅的图像话题'
        ),
        Node(
            package='video_recorder',
            executable='video_recorder',
            name='video_recorder_node',
            output='screen',
            parameters=[{
                'output_dir': LaunchConfiguration('output_dir'),
                'filename_prefix': LaunchConfiguration('filename_prefix'),
                'fps': LaunchConfiguration('fps'),
                'fourcc': LaunchConfiguration('fourcc'),
                'topic': LaunchConfiguration('topic'),
            }],
        )
    ]) 