from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='storm_gazebo_magnet',
            executable='storm_gazebo_dipole_magnet',
            name='dipole_magnet',
            output='screen',
        ),
    ])
