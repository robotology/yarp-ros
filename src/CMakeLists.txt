# SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
# SPDX-License-Identifier: BSD-3-Clause

# public libraries
add_subdirectory(libYARP_rosmsg)

# private libraries
add_subdirectory(libYARP_wire_rep_utils)

# plugins
add_subdirectory(carriers)

if(YARP_COMPILE_EXECUTABLES)
    # idl compilers (thrift and ros)
    add_subdirectory(yarpidl_rosmsg)
    if(NOT CREATE_SHARED_LIBS)
        include(YarpInstallBasicPackageFiles)
        yarp_install_basic_package_files(
          YARP_idl_tools
          INCLUDE_CONTENT "include(\"\\\${YARP_MODULE_DIR}/YarpIDL.cmake\")"
        )
    endif()
endif()
