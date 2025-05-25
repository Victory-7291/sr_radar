from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import SetEnvironmentVariable

def generate_launch_description():
    # 设置ROS2日志级别
    stdout_linebuf_envvar = SetEnvironmentVariable(
        'RCUTILS_LOGGING_BUFFERED_STREAM', '1')
        
    return LaunchDescription([
        stdout_linebuf_envvar,
        Node(
            package='radar_warn',
            executable='radar_warn_node',
            name='radar_warn',
            output='screen',
            arguments=['--ros-args', '--log-level', 'info'],
            emulate_tty=True,
        )
    ]) 