/*
 * SPDX-FileCopyrightText: 2006-2021 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: BSD-3-Clause
 */

// This is an automatically generated file.

// Generated from the following "geometry_msgs/Quaternion" msg definition:
//   # This represents an orientation in free space in quaternion form.
//   
//   float64 x
//   float64 y
//   float64 z
//   float64 w
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_geometry_msgs_Quaternion_h
#define YARP_ROSMSG_geometry_msgs_Quaternion_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>

namespace yarp {
namespace rosmsg {
namespace geometry_msgs {

class Quaternion : public yarp::os::idl::WirePortable
{
public:
    yarp::conf::float64_t x;
    yarp::conf::float64_t y;
    yarp::conf::float64_t z;
    yarp::conf::float64_t w;

    Quaternion() :
            x(0.0),
            y(0.0),
            z(0.0),
            w(0.0)
    {
    }

    void clear()
    {
        // *** x ***
        x = 0.0;

        // *** y ***
        y = 0.0;

        // *** z ***
        z = 0.0;

        // *** w ***
        w = 0.0;
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** x ***
        x = connection.expectFloat64();

        // *** y ***
        y = connection.expectFloat64();

        // *** z ***
        z = connection.expectFloat64();

        // *** w ***
        w = connection.expectFloat64();

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(4)) {
            return false;
        }

        // *** x ***
        x = reader.expectFloat64();

        // *** y ***
        y = reader.expectFloat64();

        // *** z ***
        z = reader.expectFloat64();

        // *** w ***
        w = reader.expectFloat64();

        return !connection.isError();
    }

    using yarp::os::idl::WirePortable::read;
    bool read(yarp::os::ConnectionReader& connection) override
    {
        return (connection.isBareMode() ? readBare(connection)
                                        : readBottle(connection));
    }

    bool writeBare(yarp::os::ConnectionWriter& connection) const override
    {
        // *** x ***
        connection.appendFloat64(x);

        // *** y ***
        connection.appendFloat64(y);

        // *** z ***
        connection.appendFloat64(z);

        // *** w ***
        connection.appendFloat64(w);

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) const override
    {
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(4);

        // *** x ***
        connection.appendInt32(BOTTLE_TAG_FLOAT64);
        connection.appendFloat64(x);

        // *** y ***
        connection.appendInt32(BOTTLE_TAG_FLOAT64);
        connection.appendFloat64(y);

        // *** z ***
        connection.appendInt32(BOTTLE_TAG_FLOAT64);
        connection.appendFloat64(z);

        // *** w ***
        connection.appendInt32(BOTTLE_TAG_FLOAT64);
        connection.appendFloat64(w);

        connection.convertTextMode();
        return !connection.isError();
    }

    using yarp::os::idl::WirePortable::write;
    bool write(yarp::os::ConnectionWriter& connection) const override
    {
        return (connection.isBareMode() ? writeBare(connection)
                                        : writeBottle(connection));
    }

    // This class will serialize ROS style or YARP style depending on protocol.
    // If you need to force a serialization style, use one of these classes:
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::geometry_msgs::Quaternion> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::geometry_msgs::Quaternion> bottleStyle;

    // The name for this message, ROS will need this
    static constexpr const char* typeName = "geometry_msgs/Quaternion";

    // The checksum for this message, ROS will need this
    static constexpr const char* typeChecksum = "a779879fadf0160734f906b8c19c7004";

    // The source text for this message, ROS will need this
    static constexpr const char* typeText = "\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
";

    yarp::os::Type getType() const override
    {
        yarp::os::Type typ = yarp::os::Type::byName(typeName, typeName);
        typ.addProperty("md5sum", yarp::os::Value(typeChecksum));
        typ.addProperty("message_definition", yarp::os::Value(typeText));
        return typ;
    }
};

} // namespace geometry_msgs
} // namespace rosmsg
} // namespace yarp

#endif // YARP_ROSMSG_geometry_msgs_Quaternion_h
