# SPDX-FileCopyrightText: 2006-2021 Istituto Italiano di Tecnologia (IIT)
# SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)

# UseSWIG generates now standard target names.
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.13)
  cmake_policy(SET CMP0078 OLD)
endif()

# UseSWIG honors SWIG_MODULE_NAME via -module flag.
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.14)
  cmake_policy(SET CMP0086 OLD)
endif()

# Main project
project(
  YARP-ros
  VERSION 3.9.0
  LANGUAGES C CXX
)
set(PROJECT_DESCRIPTION "YARP-ros: ros interfaces and plugins for YARP")


# Pick up our CMake scripts - they are all in the cmake subdirectory.
set(YARP_MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_DIR})

# Find YCM
# This is required here, because YarpVersion uses GitInfo from YCM
set(YCM_REQUIRED_VERSION 0.15.1) # Used also by YarpFindDependencies
find_package(YCM ${YCM_REQUIRED_VERSION} REQUIRED)
find_package(YARP 3.8.0 COMPONENTS os sig dev serversql OPTIONAL_COMPONENTS math REQUIRED)
find_package(YARP 3.8.0 COMPONENTS catch2 QUIET)

# Get the current YARP version.
# See cmake/YarpVersion.cmake.
#include(YarpVersion)

set_property(GLOBAL PROPERTY USE_FOLDERS 1)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER "Autogen Targets")
set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP "Generated Files")

# Check system configuration.
# See cmake/YarpSystemCheck.cmake.
#include(YarpSystemCheck)
include(CheckCXXCompilerFlag)

# Set up some compilation options.
# See cmake/YarpOptions.cmake.
#include(YarpOptions)

#########################################################################
# Compile libraries using -fPIC to produce position independent code.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#########################################################################
# Control whether libraries are shared or static (imported from YarpOptions)

option(BUILD_SHARED_LIBS "Compile shared libraries rather than linking statically" ON)
mark_as_advanced(BUILD_SHARED_LIBS)

set(YARP_DLL OFF)
if(BUILD_SHARED_LIBS)
  set(YARP_DLL ON)
endif()

set (YARP_LINK_PLUGINS TRUE)
if(YARP_FORCE_DYNAMIC_PLUGINS OR BUILD_SHARED_LIBS)
  set (YARP_LINK_PLUGINS FALSE)
endif()

#########################################################################
# Turn on testing  (imported from YarpOptions)

option(YARP_COMPILE_TESTS "Enable YARP tests" OFF)
if(YARP_COMPILE_TESTS)
  enable_testing()
endif()

#########################################################################
# Other stuff

message(STATUS "Using:")
message(STATUS "  CMake: ${CMAKE_VERSION} (${CMAKE_COMMAND})")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} (${CMAKE_C_COMPILER})")
message(STATUS "  CXX Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} (${CMAKE_CXX_COMPILER})")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMake modules directory: ${CMAKE_MODULE_PATH}")

# Check YARP dependencies, find necessary libraries.
# See cmake/YarpFindDependencies.cmake.
include(YarpFindDependencies)

# Make some custom header files containing compile settings.
#add_subdirectory(cmake)

# Build required 3rd party libraries
add_subdirectory(extern)

#include(YarpInstallationHelpers)
#include(YarpDeprecatedOption)

#yarp_configure_plugins_installation(${PROJECT_NAME})
yarp_configure_external_installation(yarp WITH_PLUGINS)
set(YARP_COMPILE_EXECUTABLES TRUE)

# Set up the main libraries and utilities.
add_subdirectory(src)

# Offer to compile bindings
# add_subdirectory(bindings)

# Tests
add_subdirectory(tests)

# Examples
#add_subdirectory(example)

# Platform independent data
#add_subdirectory(data)

# Documentation
#add_subdirectory(doc)

# Output configuration files describing how YARP was built, and how
# its libraries may be linked against and used.  This uses
# information accumulated in the global property variables set up earlier.
# See cmake/YarpDescribe.cmake
#include(YarpDescribe)

# Set up some packaging properties (for generating tarballs etc).
# See cmake/YarpPackage.cmake
#include(YarpPackage)


# add rule for uninstalling YARP
include(AddUninstallTarget)
