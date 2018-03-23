/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "tf2_msgs/FrameGraph" msg definition:
//   ---
//   string frame_yaml
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_tf2_msgs_FrameGraph_h
#define YARP_ROSMSG_tf2_msgs_FrameGraph_h

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>

namespace yarp {
namespace rosmsg {
namespace tf2_msgs {

class FrameGraph : public yarp::os::idl::WirePortable
{
public:

    FrameGraph()
    {
    }

    void clear()
    {
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(0)) {
            return false;
        }


        return !connection.isError();
    }

    using yarp::os::idl::WirePortable::read;
    bool read(yarp::os::ConnectionReader& connection) override
    {
        return (connection.isBareMode() ? readBare(connection)
                                        : readBottle(connection));
    }

    bool writeBare(yarp::os::ConnectionWriter& connection) override
    {

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) override
    {
        connection.appendInt(BOTTLE_TAG_LIST);
        connection.appendInt(0);


        connection.convertTextMode();
        return !connection.isError();
    }

    using yarp::os::idl::WirePortable::write;
    bool write(yarp::os::ConnectionWriter& connection) override
    {
        return (connection.isBareMode() ? writeBare(connection)
                                        : writeBottle(connection));
    }

    // This class will serialize ROS style or YARP style depending on protocol.
    // If you need to force a serialization style, use one of these classes:
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::tf2_msgs::FrameGraph> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::tf2_msgs::FrameGraph> bottleStyle;

    // Give source text for class, ROS will need this
    static yarp::os::ConstString typeText()
    {
        return yarp::os::ConstString("\
---\n\
string frame_yaml\n\
");
    }

    yarp::os::ConstString getTypeText() const
    {
        return yarp::rosmsg::tf2_msgs::FrameGraph::typeText();
    }

    // Name the class, ROS will need this
    yarp::os::Type getType() override
    {
        yarp::os::Type typ = yarp::os::Type::byName("tf2_msgs/FrameGraph", "tf2_msgs/FrameGraph");
        typ.addProperty("md5sum", yarp::os::Value("d41d8cd98f00b204e9800998ecf8427e"));
        typ.addProperty("message_definition", yarp::os::Value(getTypeText()));
        return typ;
    }
};

} // namespace tf2_msgs
} // namespace rosmsg
} // namespace yarp

#endif // YARP_ROSMSG_tf2_msgs_FrameGraph_h
