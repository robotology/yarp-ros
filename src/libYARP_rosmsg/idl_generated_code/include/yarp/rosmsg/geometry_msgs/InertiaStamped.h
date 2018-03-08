// This is an automatically generated file.

// Generated from the following "geometry_msgs/InertiaStamped" msg definition:
//   Header header
//   Inertia inertia
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_geometry_msgs_InertiaStamped_h
#define YARP_ROSMSG_geometry_msgs_InertiaStamped_h

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>
#include <yarp/rosmsg/std_msgs/Header.h>
#include <yarp/rosmsg/geometry_msgs/Inertia.h>

namespace yarp {
namespace rosmsg {
namespace geometry_msgs {

class InertiaStamped : public yarp::os::idl::WirePortable
{
public:
    yarp::rosmsg::std_msgs::Header header;
    yarp::rosmsg::geometry_msgs::Inertia inertia;

    InertiaStamped() :
            header(),
            inertia()
    {
    }

    void clear()
    {
        // *** header ***
        header.clear();

        // *** inertia ***
        inertia.clear();
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** header ***
        if (!header.read(connection)) {
            return false;
        }

        // *** inertia ***
        if (!inertia.read(connection)) {
            return false;
        }

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(2)) {
            return false;
        }

        // *** header ***
        if (!header.read(connection)) {
            return false;
        }

        // *** inertia ***
        if (!inertia.read(connection)) {
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
        // *** header ***
        if (!header.write(connection)) {
            return false;
        }

        // *** inertia ***
        if (!inertia.write(connection)) {
            return false;
        }

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) override
    {
        connection.appendInt(BOTTLE_TAG_LIST);
        connection.appendInt(2);

        // *** header ***
        if (!header.write(connection)) {
            return false;
        }

        // *** inertia ***
        if (!inertia.write(connection)) {
            return false;
        }

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
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::geometry_msgs::InertiaStamped> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::geometry_msgs::InertiaStamped> bottleStyle;

    // Give source text for class, ROS will need this
    yarp::os::ConstString getTypeText()
    {
        return "Header header\n\
Inertia inertia\n================================================================================\n\
MSG: std_msgs/Header\n\
\n================================================================================\n\
MSG: geometry_msgs/Inertia\n\
";
    }

    // Name the class, ROS will need this
    yarp::os::Type getType() override
    {
        yarp::os::Type typ = yarp::os::Type::byName("geometry_msgs/InertiaStamped", "geometry_msgs/InertiaStamped");
        typ.addProperty("md5sum", yarp::os::Value("d41d8cd98f00b204e9800998ecf8427e"));
        typ.addProperty("message_definition", yarp::os::Value(getTypeText()));
        return typ;
    }
};

} // namespace geometry_msgs
} // namespace rosmsg
} // namespace yarp

#endif // YARP_ROSMSG_geometry_msgs_InertiaStamped_h
