# SPDX-FileCopyrightText: 2006-2021 Istituto Italiano di Tecnologia (IIT)
# SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
# SPDX-License-Identifier: BSD-3-Clause

include(YarpPlugin)
include(YarpPrintFeature)

yarp_begin_plugin_library(yarpcarros
  OPTION YARP_COMPILE_CARRIER_PLUGINS
  DEFAULT ON
)

add_subdirectory(xmlrpc_carrier)
add_subdirectory(tcpros_carrier)

yarp_end_plugin_library(yarpcarros QUIET)
add_library(YARP::yarpcarros ALIAS yarpcarros)

install(
  TARGETS yarpcarros
  EXPORT YARP_yarpcarros
  COMPONENT yarpcarros
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

include(YarpInstallBasicPackageFiles)
yarp_install_basic_package_files(YARP_yarpcarros
  DEPENDENCIES ${YARP_yarpcarros_PUBLIC_DEPS}
  PRIVATE_DEPENDENCIES ${YARP_yarpcarros_PRIVATE_DEPS}
)

set_property(TARGET yarpcarros PROPERTY FOLDER "Plugins/Carrier")
