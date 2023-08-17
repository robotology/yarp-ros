# SPDX-FileCopyrightText: 2006-2021 Istituto Italiano di Tecnologia (IIT)
# SPDX-License-Identifier: BSD-3-Clause

#########################################################################
# Wrapper for the catch_discover_tests that also enables colors, and sets
# the TIMEOUT and SKIP_RETURN_CODE test properties.

include (Catch)

function(yarp_catch_discover_tests _target)
  # Workaround to force catch_discover_tests to run tests under valgrind
  set_property(TARGET ${_target} PROPERTY CROSSCOMPILING_EMULATOR "${YARP_TEST_LAUNCHER}")
  catch_discover_tests(
    ${_target}
    EXTRA_ARGS "-s" "--colour-mode default"
    PROPERTIES
      TIMEOUT ${YARP_TEST_TIMEOUT}
      SKIP_RETURN_CODE 254
    )
endfunction()


function(create_device_test test_name)
    if (DEFINED ${ARGV1})
      set (extra_libs ${ARGV1})
    endif()

    add_executable(harness_dev_${test_name})
    target_sources(harness_dev_${test_name}
      PRIVATE
        ${test_name}_test.cpp
    )
    target_link_libraries(harness_dev_${test_name}
      PRIVATE
        YARP_harness
        YARP::YARP_os
        YARP::YARP_sig
        YARP::YARP_dev
        YARP::YARP_dev_tests
        ${extra_libs}
    )
    set_property(TARGET harness_dev_${test_name} PROPERTY FOLDER "Test")
    yarp_catch_discover_tests(harness_dev_${test_name})
endfunction()
