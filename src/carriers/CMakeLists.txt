# SPDX-FileCopyrightText: 2006-2021 Istituto Italiano di Tecnologia (IIT)
# SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
# SPDX-License-Identifier: BSD-3-Clause

include(YarpPlugin)
include(YarpPrintFeature)

yarp_begin_plugin_library(yarpcar
  OPTION YARP_COMPILE_CARRIER_PLUGINS
  DEFAULT ON
)

#  add_subdirectory(xmlrpc_carrier)
  add_subdirectory(tcpros_carrier)

yarp_end_plugin_library(yarpcar QUIET)
add_library(YARP::yarpcar ALIAS yarpcar)

install(
  TARGETS yarpcar
  EXPORT YARP_yarpcar
  COMPONENT yarpcar
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

include(YarpInstallBasicPackageFiles)
yarp_install_basic_package_files(YARP_yarpcar
  DEPENDENCIES ${YARP_yarpcar_PUBLIC_DEPS}
  PRIVATE_DEPENDENCIES ${YARP_yarpcar_PRIVATE_DEPS}
)

set_property(TARGET yarpcar PROPERTY FOLDER "Plugins/Carrier")