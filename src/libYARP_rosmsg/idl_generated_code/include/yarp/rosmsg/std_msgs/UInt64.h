/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "std_msgs/UInt64" msg definition:
//   uint64 data// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_std_msgs_UInt64_h
#define YARP_ROSMSG_std_msgs_UInt64_h

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>

namespace yarp {
namespace rosmsg {
namespace std_msgs {

class UInt64 : public yarp::os::idl::WirePortable
{
public:
    std::uint64_t data;

    UInt64() :
            data(0)
    {
    }

    void clear()
    {
        // *** data ***
        data = 0;
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** data ***
        data = connection.expectInt64();

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(1)) {
            return false;
        }

        // *** data ***
        data = reader.expectInt64();

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
        // *** data ***
        connection.appendInt64(data);

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) override
    {
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(1);

        // *** data ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(data);

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
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::std_msgs::UInt64> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::std_msgs::UInt64> bottleStyle;

    // Give source text for class, ROS will need this
    static std::string typeText()
    {
        return std::string("\
uint64 data");
    }

    std::string getTypeText() const
    {
        return yarp::rosmsg::std_msgs::UInt64::typeText();
    }

    // Name the class, ROS will need this
    yarp::os::Type getType() override
    {
        yarp::os::Type typ = yarp::os::Type::byName("std_msgs/UInt64", "std_msgs/UInt64");
        typ.addProperty("md5sum", yarp::os::Value("1b2a79973e8bf53d7b53acb71299cb57"));
        typ.addProperty("message_definition", yarp::os::Value(getTypeText()));
        return typ;
    }
};

} // namespace std_msgs
} // namespace rosmsg
} // namespace yarp

#endif // YARP_ROSMSG_std_msgs_UInt64_h
