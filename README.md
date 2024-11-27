## yarp-ros

> [!WARNING]  
> The functionality that provide compatibility between YARP and ROS 1 are deprecated and will be removed in YARP 3.11 . Please migrate to use https://github.com/robotology/yarp-devices-ros2 instead.
> This repository permit to continue to use ROS 1 with YARP 3.10, but will not work with YARP 3.11 .

This repository contains the following functionality that used to be part of the main YARP repository, and were moved in this repo in YARP 3.10:
* The carriers `tcpros` and `xmlrpc`, used for ROS 1 compatibility at port protocol level,
* the `rosmsg` YARP IDL code generator, used to generate YARP serializable classes out of ROS's `.msg` definitions.

This is quite a standard CMake repository that can be installed using the usual CMake process for installing packages.
