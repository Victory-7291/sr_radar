from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='radar_warn',
            executable='radar_warn_node',
            name='radar_warn',
            output='screen',
            emulate_tty=True,
        )
    ]) 