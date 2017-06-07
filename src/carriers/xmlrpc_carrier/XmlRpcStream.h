/*
 * Copyright (C) 2010 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef YARP_XMLRPC_CARRIER_XMLRPCSTREAM_H
#define YARP_XMLRPC_CARRIER_XMLRPCSTREAM_H

#include <yarp/os/InputStream.h>
#include <yarp/os/OutputStream.h>
#include <yarp/os/TwoWayStream.h>
#include <yarp/os/StringInputStream.h>
#include <yarp/os/StringOutputStream.h>

#include "XmlRpcClient.h"
#include "XmlRpcServerConnection.h"

namespace yarp {
    namespace os {
        class XmlRpcStream;
    }
}

class yarp::os::XmlRpcStream : public TwoWayStream,
                               public InputStream,
                               public OutputStream
{
private:
    TwoWayStream *delegate;
    YarpXmlRpc::XmlRpcClient client;
    YarpXmlRpc::XmlRpcServerConnection server;
    StringInputStream sis;
    StringOutputStream sos;
    bool sender;
    bool firstRound;
    bool interpretRos;
public:
    XmlRpcStream(TwoWayStream *delegate, bool sender, bool interpretRos) :
            client("notset", 0),
            server(0, YARP_NULLPTR),
            sender(sender),
            interpretRos(interpretRos)
    {
        this->delegate = delegate;
        client.reset();
        server.reset();
        firstRound = true;
    }

    virtual ~XmlRpcStream()
    {
        if (delegate != YARP_NULLPTR) {
            delete delegate;
            delegate = YARP_NULLPTR;
        }
    }

    virtual yarp::os::InputStream& getInputStream() override
    {
        return *this;
    }

    virtual yarp::os::OutputStream& getOutputStream() override
    {
        return *this;
    }


    virtual const yarp::os::Contact& getLocalAddress() override
    {
        return delegate->getLocalAddress();
    }

    virtual const yarp::os::Contact& getRemoteAddress() override
    {
        return delegate->getRemoteAddress();
    }

    virtual bool isOk() override
    {
        return delegate->isOk();
    }

    virtual void reset() override
    {
        delegate->reset();
    }

    virtual void close() override
    {
        delegate->close();
    }

    virtual void beginPacket() override
    {
        delegate->beginPacket();
    }

    virtual void endPacket() override
    {
        delegate->endPacket();
    }

    using yarp::os::OutputStream::write;
    virtual void write(const Bytes& b) override;

    using yarp::os::InputStream::read;
    virtual YARP_SSIZE_T read(const Bytes& b) override;

    virtual void interrupt() override
    {
        delegate->getInputStream().interrupt();
    }

};

#endif // YARP_XMLRPC_CARRIER_XMLRPCSTREAM_H
