# SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
# SPDX-License-Identifier: BSD-3-Clause

# public libraries
add_subdirectory(libYARP_rosmsg)

# private libraries
add_subdirectory(libYARP_wire_rep_utils)

# plugins
add_subdirectory(carriers)

if(YARP_COMPILE_EXECUTABLES)
    # ros idl compiler
    add_subdirectory(yarpidl_rosmsg)
endif()
