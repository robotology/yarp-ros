# SPDX-FileCopyrightText: 2006-2021 Istituto Italiano di Tecnologia (IIT)
# SPDX-License-Identifier: BSD-3-Clause

# disable all warnings for current folder and subfolders
# (unless explicitly added by the user)
get_property(_USER_CMAKE_C_FLAGS CACHE CMAKE_C_FLAGS PROPERTY VALUE)
get_property(_USER_CMAKE_CXX_FLAGS CACHE CMAKE_CXX_FLAGS PROPERTY VALUE)
set(CMAKE_C_FLAGS "-w ${_USER_CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "-w ${_USER_CMAKE_CXX_FLAGS}")

# XmlRpc++
if(YARP_BUILD_xmlrpcpp)
  add_subdirectory(xmlrpcpp)
  set(xmlrpcpp_INCLUDE_DIRS ${xmlrpcpp_INCLUDE_DIRS} PARENT_SCOPE)
  set(xmlrpcpp_LIBRARIES ${xmlrpcpp_LIBRARIES} PARENT_SCOPE)
  set(xmlrpcpp_DEFINITIONS ${xmlrpcpp_DEFINITIONS} PARENT_SCOPE)
endif()

# Apache Thrift
set(THRIFT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/thrift/thrift" PARENT_SCOPE)

# diff_match_patch
set(diff_match_patch_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/diff_match_patch" PARENT_SCOPE)

# dirent (for MSVC)
if(MSVC)
  set(dirent_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dirent/dirent/include" PARENT_SCOPE)
endif()

# md5
set(md5_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/md5" PARENT_SCOPE)

# ROS messages
unset(ROS_MSG_PACKAGES)

#   * std_msgs
list(APPEND ROS_MSG_PACKAGES std_msgs)
set(ROS_std_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/std_msgs" PARENT_SCOPE)
#   * actionlib_msgs
set(ROS_actionlib_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/common_msgs/actionlib_msgs" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES actionlib_msgs)
#   * diagnostic_msgs
set(ROS_diagnostic_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/common_msgs/diagnostic_msgs" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES diagnostic_msgs)
#   * geometry_msgs
set(ROS_geometry_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/common_msgs/geometry_msgs" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES geometry_msgs)
#   * nav_msgs
set(ROS_nav_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/common_msgs/nav_msgs" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES nav_msgs)
#   * sensor_msgs
set(ROS_sensor_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/common_msgs/sensor_msgs" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES sensor_msgs)
#   * shape_msgs
set(ROS_shape_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/common_msgs/shape_msgs" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES shape_msgs)
#   * stereo_msgs
set(ROS_stereo_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/common_msgs/stereo_msgs" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES stereo_msgs)
#   * trajectory_msgs
set(ROS_trajectory_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/common_msgs/trajectory_msgs" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES trajectory_msgs)
#   * visualization_msgs
set(ROS_visualization_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/common_msgs/visualization_msgs" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES visualization_msgs)
#   * tf
set(ROS_tf_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/geometry/tf" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES tf)
#   * tf2_msgs
set(ROS_tf2_msgs_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ros/geometry2/tf2_msgs" PARENT_SCOPE)
list(APPEND ROS_MSG_PACKAGES tf2_msgs)

set(ROS_MSG_PACKAGES ${ROS_MSG_PACKAGES} PARENT_SCOPE)

