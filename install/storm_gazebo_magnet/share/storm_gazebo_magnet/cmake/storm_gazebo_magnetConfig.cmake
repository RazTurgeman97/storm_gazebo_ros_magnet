# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_storm_gazebo_magnet_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED storm_gazebo_magnet_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(storm_gazebo_magnet_FOUND FALSE)
  elseif(NOT storm_gazebo_magnet_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(storm_gazebo_magnet_FOUND FALSE)
  endif()
  return()
endif()
set(_storm_gazebo_magnet_CONFIG_INCLUDED TRUE)

# output package information
if(NOT storm_gazebo_magnet_FIND_QUIETLY)
  message(STATUS "Found storm_gazebo_magnet: 0.1.0 (${storm_gazebo_magnet_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'storm_gazebo_magnet' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${storm_gazebo_magnet_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(storm_gazebo_magnet_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${storm_gazebo_magnet_DIR}/${_extra}")
endforeach()
