cmake_minimum_required(VERSION 3.5)
project(storm_gazebo_magnet)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(ignition-gazebo6 REQUIRED)
find_package(ignition-math6 REQUIRED)

# Include directories
include_directories(include)

# Add plugin library
add_library(storm_gazebo_dipole_magnet SHARED src/dipole_magnet.cc)
ament_target_dependencies(storm_gazebo_dipole_magnet
    rclcpp
    std_msgs
    geometry_msgs
    ignition-gazebo6
    ignition-math6
)

# Install
install(TARGETS storm_gazebo_dipole_magnet
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
