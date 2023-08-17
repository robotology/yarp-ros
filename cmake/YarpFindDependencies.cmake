# SPDX-FileCopyrightText: 2006-2021 Istituto Italiano di Tecnologia (IIT)
# SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
# SPDX-License-Identifier: BSD-3-Clause

# This module checks if all the dependencies are installed and if the
# dependencies to build some parts of YARP are satisfied.
# For every dependency, it creates the following variables:
#
# YARP_USE_${Package}: Can be disabled by the user if he doesn't want to use that
#                      dependency.
# YARP_HAS_${Package}: Internal flag. It should be used to check if a part of
#                      YARP should be built. It is on if YARP_USE_${Package} is
#                      on and either the package was found or will be built.
# YARP_BUILD_${Package}: Internal flag. Used to check if YARP has to build an
#                        external package.
# YARP_BUILD_DEPS_${Package}: Internal flag. Used to check if dependencies
#                             required to build the package are available.
# YARP_HAS_SYSTEM_${Package}: Internal flag. Used to check if the package is
#                             available on the system.
# YARP_USE_SYSTEM_${Package}: This flag is shown only for packages in the
#                             extern folder that were also found on the system
#                             (TRUE by default). If this flag is enabled, the
#                             system installed library will be used instead of
#                             the version shipped with YARP.


include(YarpRenamedOption)
include(CMakeDependentOption)
include(YarpPrintFeature)

# USEFUL MACROS:

# Check if a package is installed and set some cmake variables
macro(checkandset_dependency package)

  string(TOUPPER ${package} PKG)

  # YARP_HAS_SYSTEM_${package}
  if(${package}_FOUND OR ${PKG}_FOUND)
    set(YARP_HAS_SYSTEM_${package} TRUE)
  else()
    set(YARP_HAS_SYSTEM_${package} FALSE)
  endif()

  # YARP_USE_${package}
  cmake_dependent_option(YARP_USE_${package} "Use package ${package}" TRUE
                         YARP_HAS_SYSTEM_${package} FALSE)
  if(NOT "${package}" STREQUAL "${PKG}")
    yarp_renamed_option(YARP_USE_${PKG} YARP_USE_${package}) # Deprecated since YARP 3.2
  endif()
  mark_as_advanced(YARP_USE_${package})

  # YARP_USE_SYSTEM_${package}
  set(YARP_USE_SYSTEM_${package} ${YARP_USE_${package}} CACHE INTERNAL "Use system-installed ${package}, rather than a private copy (recommended)" FORCE)
  if(NOT "${package}" STREQUAL "${PKG}")
    unset(YARP_USE_SYSTEM_${PKG} CACHE) # Deprecated since YARP 3.2
  endif()

  # YARP_HAS_${package}
  if(${YARP_HAS_SYSTEM_${package}})
    set(YARP_HAS_${package} ${YARP_USE_${package}})
  else()
    set(YARP_HAS_${package} FALSE)
  endif()

endmacro()


# Check if a package is installed or if is going to be built and set some cmake variables
macro(checkbuildandset_dependency package)

  string(TOUPPER ${package} PKG)

  # YARP_HAS_SYSTEM_${package}
  if (${package}_FOUND OR ${PKG}_FOUND)
    set(YARP_HAS_SYSTEM_${package} TRUE)
  else()
    set(YARP_HAS_SYSTEM_${package} FALSE)
  endif()

  # YARP_BUILD_DEPS_${package}
  set(YARP_BUILD_DEPS_${package} 1)
  if(${ARGC} GREATER 1)
    foreach(_dep ${ARGN})
      if(NOT YARP_HAS_${_dep})
        set(YARP_BUILD_DEPS_${package} 0)
      endif()
    endforeach()
  endif()

  # YARP_USE_${package}
  cmake_dependent_option(YARP_USE_${package} "Use package ${package}" TRUE
                         "YARP_HAS_SYSTEM_${package} OR YARP_BUILD_DEPS_${package}" FALSE)
  mark_as_advanced(YARP_USE_${package})
  if(NOT "${package}" STREQUAL "${PKG}")
    yarp_renamed_option(YARP_USE_${PKG} YARP_USE_${package}) # Deprecated since YARP 3.2
  endif()

  # YARP_USE_SYSTEM_${package}
  cmake_dependent_option(YARP_USE_SYSTEM_${package} "Use system-installed ${package}, rather than a private copy (recommended)" TRUE
                         "YARP_HAS_SYSTEM_${package};YARP_USE_${package}" FALSE)
  mark_as_advanced(YARP_USE_SYSTEM_${package})
  if(NOT "${package}" STREQUAL "${PKG}")
    yarp_renamed_option(YARP_USE_SYSTEM_${PKG} YARP_USE_SYSTEM_${package}) # Deprecated since YARP 3.2
  endif()

  # YARP_HAS_${package}
  set(YARP_HAS_${package} ${YARP_USE_${package}})

  # YARP_BUILD_${package}
  if(YARP_USE_${package} AND NOT YARP_USE_SYSTEM_${package} AND YARP_BUILD_DEPS_${package})
    set(YARP_BUILD_${package} TRUE)
  else()
    set(YARP_BUILD_${package} FALSE)
  endif()

endmacro()

# Always build some package and set some cmake variables
macro(buildandset_dependency package)

  set(YARP_HAS_SYSTEM_${package} FALSE)

  # YARP_USE_${package}
  option(YARP_USE_${package} "Use package ${package}" TRUE)
  mark_as_advanced(YARP_USE_${package})

  # YARP_HAS_${package}
  set(YARP_HAS_${package} ${YARP_USE_${package}})

  # YARP_BUILD_${package}
  set(YARP_BUILD_${package} TRUE)

  if(YARP_USE_${package})
    if(${ARGC} GREATER 1)
      foreach(_dep ${ARGN})
        string(TOUPPER ${_dep} _DEP)
        if(NOT YARP_HAS_${_DEP})
          message(WARNING "${_dep} (required to build ${package}) not found.")
          set(YARP_HAS_${package} FALSE)
          set(YARP_BUILD_${package} FALSE)
        endif()
      endforeach()
    endif()
  endif()

endmacro()




# Check if a required package is installed.
macro(check_required_dependency package)
  if(NOT YARP_HAS_${package})
    message(FATAL_ERROR "Required package ${package} not found. Please install it to build yarp.")
  endif()
endmacro()


# Check if a dependency required to enable an option is installed.
macro(check_optional_dependency optionname package)
  if(${optionname})
    if(NOT YARP_HAS_${package})
      message(FATAL_ERROR "Optional package ${package} not found. Please install it or disable the option \"${optionname}\" to build yarp.")
    endif()
  endif()
endmacro()


# Check if at least one of the dependency required to enable an option is installed.
function(check_alternative_dependency optionname)
  if(${optionname})
    foreach(package "${ARGN}")
      if(YARP_HAS_${package})
        return()
      endif()
    endforeach()
    message(FATAL_ERROR "None of the alternative packages \"${ARGN}\" was found. Please install at least one of them or disable the option \"${optionname}\" to build yarp.")
  endif()
endfunction()


# Check if a dependency required to disable an option is installed.
macro(check_skip_dependency optionname package)
  if(NOT ${optionname})
    if(NOT YARP_HAS_${package})
      message(FATAL_ERROR "Optional package ${package} not found. Please install it or enable the option \"${optionname}\" to build yarp.")
    endif()
  endif()
endmacro()


# Print status for a dependency
macro(print_dependency package)

  string(TOUPPER ${package} PKG)

#  message("YARP_HAS_SYSTEM_${package} = ${YARP_HAS_SYSTEM_${package}}")
#  message("YARP_USE_${package} = ${YARP_USE_${package}}")
#  message("YARP_USE_SYSTEM_${package} = ${YARP_USE_SYSTEM_${package}}")
#  message("YARP_HAS_${package} = ${YARP_HAS_${package}}")
#  if(NOT "${YARP_BUILD_${package}}" STREQUAL "")
#    message("YARP_BUILD_${package} = ${YARP_BUILD_${package}}")
#    message("YARP_BUILD_DEPS_${package} = ${YARP_BUILD_DEPS_${package}}")
#  endif()

  if(DEFINED ${package}_REQUIRED_VERSION)
    set(_required_version " (>= ${${package}_REQUIRED_VERSION})")
  endif()
  if(DEFINED ${package}_VERSION)
    set(_version " ${${package}_VERSION}")
  endif()
  yarp_colorize_string(_help black 1 "CMAKE_DISABLE_FIND_PACKAGE_${package}")
  if(NOT DEFINED YARP_HAS_${package})
    set(_reason "disabled")
    set(_color yellow)
  elseif(NOT YARP_HAS_${package} AND DEFINED YARP_BUILD_DEPS_${package} AND NOT YARP_BUILD_DEPS_${package})
    set(_reason "build dependencies missing")
    set(_color red)
  elseif(NOT YARP_HAS_${package})
    if (${CMAKE_DISABLE_FIND_PACKAGE_${package}})
      set(_reason "disabled by the user (${_help})")
      set(_color yellow)
    else(NOT YARP_HAS_${package})
      set(_reason "not found")
      set(_color red)
    endif()
  elseif(YARP_HAS_SYSTEM_${package} AND YARP_USE_SYSTEM_${package})
    unset(_where)
    if(${package}_DIR)
      set(_where " (${${package}_DIR})")
    elseif(${package}_LIBRARIES)
      list(GET ${package}_LIBRARIES 0 _lib)
      if(_lib MATCHES "^(optimized|debug)$")
        list(GET ${package}_LIBRARIES 1 _lib)
      endif()
      set(_where " (${_lib})")
    elseif(${package}_INCLUDE_DIRS)
      list(GET ${package}_INCLUDE_DIRS 0 _incl)
      set(_where " (${_incl})")
    elseif(${package}_LIBRARY)
      set(_where " (${${package}_LIBRARY})")
    elseif(${package}_INCLUDE_DIR)
      set(_where " (${${package}_INCLUDE_DIR})")
    elseif(${PKG}_LIBRARY)
      set(_where " (${${PKG}_LIBRARY})")
    elseif(${PKG}_INCLUDE_DIR)
      set(_where " (${${PKG}_INCLUDE_DIR})")
    endif()
    set(_reason "found${_version}${_where} (${_help})")
    set(_color green)
  elseif(YARP_HAS_SYSTEM_${package})
    set(_reason "compiling (system package disabled)")
    set(_color cyan)
  elseif(DEFINED YARP_CUSTOM_REASON_${package})
    set(_reason "compiling (${YARP_CUSTOM_REASON_${package}})")
    set(_color cyan)
  else()
    set(_reason "compiling (not found)")
    set(_color cyan)
  endif()

  yarp_colorize_string(_package_col ${_color} 0 "${package}")
  yarp_print_with_checkbox(YARP_HAS_${package} "${_package_col}${_required_version}: ${_reason}")

  unset(_lib)
  unset(_where)
  unset(_version)
  unset(_required_version)
  unset(_reason)
endmacro()


################################################################################
# Find all packages

# YCM is already searched in the main extern/ycm, therefore there is no need to
# look for it here.
checkandset_dependency(YCM)

set(ACE_REQUIRED_VERSION 6.0.0)
find_package(ACE ${ACE_REQUIRED_VERSION} QUIET)
checkandset_dependency(ACE)

#set(RobotTestingFramework_REQUIRED_VERSION 2)
#find_package(RobotTestingFramework ${RobotTestingFramework_REQUIRED_VERSION} QUIET)
#checkandset_dependency(RobotTestingFramework)

find_package(SQLite3 QUIET)
checkbuildandset_dependency(SQLite3)

find_package(Libedit QUIET)
checkandset_dependency(Libedit)

set(TinyXML_REQUIRED_VERSION 2.6)
find_package(TinyXML ${TinyXML_REQUIRED_VERSION} QUIET)
checkbuildandset_dependency(TinyXML)

set(YARP_CUSTOM_REASON_xmlrpcpp "customized version")
buildandset_dependency(xmlrpcpp)

set(YARP_CUSTOM_REASON_hmac "not searched")
buildandset_dependency(hmac)

set(YARP_CUSTOM_REASON_QGVCore "customized version")
find_package(QGVCore QUIET)
checkbuildandset_dependency(QGVCore Qt5 Graphviz)

set(SWIG_REQUIRED_VERSION 4)
find_package(SWIG ${SWIG_REQUIRED_VERSION} QUIET)
checkandset_dependency(SWIG)

find_package(Lua QUIET)
checkandset_dependency(Lua)

find_package(Doxygen)
checkandset_dependency(Doxygen)

################################################################################
# Options

macro(YARP_DEPENDENT_OPTION _option _doc _default _deps _force)

  if(DEFINED ${_option})
    get_property(_option_strings_set CACHE ${_option} PROPERTY STRINGS SET)
    if(_option_strings_set)
      # If the user thinks he is smarter than the machine, he deserves an error
      get_property(_option_strings CACHE ${_option} PROPERTY STRINGS)
      list(GET _option_strings 0 _option_strings_first)
      string(REGEX REPLACE ".+\"(.+)\".+" "\\1" _option_strings_first "${_option_strings_first}")
      list(LENGTH _option_strings _option_strings_length)
      math(EXPR _option_strings_last_index "${_option_strings_length} - 1")
      list(GET _option_strings ${_option_strings_last_index} _option_strings_last)
      if("${${_option}}" STREQUAL "${_option_strings_last}")
        message(SEND_ERROR "That was a trick, you cannot outsmart me! I will never let you win! ${_option} stays OFF until I say so! \"${_option_strings_first}\" is needed to enable ${_option}. Now stop bothering me, and install your dependencies, if you really want to enable this option.")
      endif()
      unset(${_option} CACHE)
    endif()
  endif()

  cmake_dependent_option(${_option} "${_doc}" ${_default} "${_deps}" ${_force})

  unset(_missing_deps)
  foreach(_dep ${_deps})
    string(REGEX REPLACE " +" ";" _depx "${_dep}")
    if(NOT (${_depx}))
      list(APPEND _missing_deps "${_dep}")
    endif()
  endforeach()

  if(DEFINED _missing_deps)
    set(${_option}_disable_reason " (dependencies unsatisfied: \"${_missing_deps}\")")
    # Set a value that can be visualized on ccmake and on cmake-gui, but
    # still evaluates to false
    set(${_option} "OFF - Dependencies unsatisfied: '${_missing_deps}' - ${_option}-NOTFOUND" CACHE STRING "${_option_doc}" FORCE)
    string(REPLACE ";" "\;" _missing_deps "${_missing_deps}")
    set_property(
      CACHE ${_option}
      PROPERTY
        STRINGS
          "OFF - Dependencies unsatisfied: '${_missing_deps}' - ${_option}-NOTFOUND"
          "OFF - You can try as much as you want, but '${_missing_deps}' is needed to enable ${_option} - ${_option}-NOTFOUND"
          "OFF - Are you crazy or what? '${_missing_deps}' is needed to enable ${_option} - ${_option}-NOTFOUND"
          "OFF - Didn't I already tell you that '${_missing_deps}' is needed to enable ${_option}? - ${_option}-NOTFOUND"
          "OFF - Stop it! - ${_option}-NOTFOUND"
          "OFF - This is insane! Leave me alone! - ${_option}-NOTFOUND"
          "ON - All right, you win. The option is enabled. Are you happy now? You just broke the build."
    )
    # Set non-cache variable that will override the value in current scope
    # For parent scopes, the "-NOTFOUND ensures that the variable still
    # evaluates to false
    set(${_option} ${_force})
  endif()

endmacro()


# FIXME Deprecate SKIP_ACE in favour of YARP_USE_ACE
# YARP_USE_ACE is marked as internal
option(SKIP_ACE "Compile YARP without ACE (Linux only, limited functionality)" OFF)
mark_as_advanced(SKIP_ACE)
if(SKIP_ACE)
  set_property(CACHE YARP_USE_ACE PROPERTY VALUE FALSE)
  unset(YARP_HAS_ACE) # Not set = disabled
elseif(YARP_HAS_SYSTEM_ACE)
  set_property(CACHE YARP_USE_ACE PROPERTY VALUE TRUE)
  set(YARP_HAS_ACE TRUE)
  set(YARP_USE_SYSTEM_ACE TRUE)
else()
  set_property(CACHE YARP_USE_ACE PROPERTY VALUE FALSE)
  set(YARP_HAS_ACE FALSE)
endif()
set_property(CACHE YARP_USE_ACE PROPERTY TYPE INTERNAL)

#yarp_dependent_option(
#  YARP_COMPILE_RobotTestingFramework_ADDONS "Compile Robot Testing Framework addons." ON
#  "YARP_HAS_RobotTestingFramework" OFF
#)

################################################################################
# Disable some parts if they are not required


set(YARP_COMPILE_libYARP_robottestingframework OFF)
if(YARP_COMPILE_RobotTestingFramework_ADDONS)
  set(YARP_COMPILE_libYARP_robottestingframework ON)
endif()

################################################################################
# Print dependencies status

message(STATUS "Libraries found:")

print_dependency(YCM)
print_dependency(ACE)
print_dependency(RobotTestingFramework)
print_dependency(SQLite3)
print_dependency(TinyXML)
print_dependency(xmlrpcpp)
print_dependency(hmac)
print_dependency(Libedit)
print_dependency(SWIG)
print_dependency(Lua)

################################################################################
# Print information for user

message(STATUS "Enabled features:")

yarp_print_feature(BUILD_SHARED_LIBS 0 "Build shared libraries")
yarp_print_feature(SKIP_ACE 0 "Disable ACE library")
yarp_print_feature(YARP_NO_DEPRECATED 0 "Filter out deprecated declarations from YARP API")
yarp_print_feature(YARP_NO_DEPRECATED_WARNINGS 1 "Do not warn when using YARP deprecated declarations")

yarp_print_feature(YARP_COMPILE_EXECUTABLES 0 "Compile executables")
yarp_print_feature(YARP_COMPILE_RobotTestingFramework_ADDONS 0 "Compile Robot Testing Framework addons")
yarp_print_feature(YARP_COMPILE_UNMAINTAINED 0 "Compile Unmaintained components")

yarp_print_feature(YARP_COMPILE_EXAMPLES 0 "Compile YARP examples")

yarp_print_feature(YARP_COMPILE_TESTS 0 "Compile and enable YARP tests")
yarp_print_feature(YARP_DISABLE_FAILING_TESTS 1 "Disable tests that fail randomly due to race conditions")
yarp_print_feature(YARP_ENABLE_BROKEN_TESTS 1 "Enable broken tests")
yarp_print_feature(YARP_ENABLE_INTEGRATION_TESTS 1 "Run integration tests")
yarp_print_feature(YARP_ENABLE_EXAMPLES_AS_TESTS 1 "Compile examples as unit tests")
yarp_print_feature(YARP_VALGRIND_TESTS 1 "Run YARP tests under Valgrind")


################################################################################
# Check options consistency

check_skip_dependency(SKIP_ACE ACE)
check_required_dependency(hmac)
check_required_dependency(SQLite3)
check_optional_dependency(YARP_COMPILE_BINDINGS SWIG)
check_optional_dependency(YARP_COMPILE_RobotTestingFramework_ADDONS RobotTestingFramework)
