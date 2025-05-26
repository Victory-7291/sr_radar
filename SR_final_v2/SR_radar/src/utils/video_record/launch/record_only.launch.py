import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import SetEnvironmentVariable

def generate_launch_description():
    # 设置ROS2日志级别
    stdout_linebuf_envvar = SetEnvironmentVariable(
        'RCUTILS_LOGGING_BUFFERED_STREAM', '1')
    
    # 定义独立的视频记录节点（当相机已经在运行时使用）
    standalone_record_node = Node(
        package='video_record',
        executable='video_record_node_exe',
        name='video_record_node',
        remappings=[
            ('camera_image', 'camera_image')
        ],
        parameters=[{
            'ros__parameters': {
                'use_sim_time': False
            }
        }],
        arguments=['--ros-args', '--log-level', 'info'],
        output='screen',
        emulate_tty=True
    )
    
    return LaunchDescription([
        stdout_linebuf_envvar,
        standalone_record_node
    ]) 