// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2010 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef TCPROSSTREAM_INC
#define TCPROSSTREAM_INC

#include <yarp/os/impl/InputStream.h>
#include <yarp/os/impl/OutputStream.h>
#include <yarp/os/impl/TwoWayStream.h>
#include <yarp/os/ManagedBytes.h>
#include <yarp/os/ConstString.h>
#include "BlobNetworkHeader.h"
#include "WireTwiddler.h"

#include <string>

namespace yarp {
    namespace os {
        namespace impl {
            class TcpRosStream;
        }
    }
}


class yarp::os::impl::TcpRosStream : public TwoWayStream, 
                                     public InputStream,
                                     public OutputStream
{
private:
    TwoWayStream *delegate;
    bool sender;
    int raw;
    bool firstRound;
    BlobNetworkHeader header;
    ManagedBytes scan;
    char *cursor;
    int remaining;
    int phase;
    bool expectTwiddle;
    WireTwiddler twiddler;
    yarp::os::ConstString kind;
    WireTwiddlerReader twiddlerReader;
public:
    TcpRosStream(TwoWayStream *delegate, bool sender,
                 bool service, int raw, const char *kind) : 
        sender(sender), raw(raw), kind(kind),
        twiddlerReader(delegate->getInputStream(),twiddler)
    {
        this->delegate = delegate;
        firstRound = true;
        phase = 0;
        expectTwiddle = service&&sender;
        updateKind(kind);
    }

    virtual ~TcpRosStream() {
        if (delegate!=NULL) {
            delete delegate;
            delegate = NULL;
        }
    }

    virtual InputStream& getInputStream() { return *this; }
    virtual OutputStream& getOutputStream() { return *this; }


    virtual const Address& getLocalAddress() {
        return delegate->getLocalAddress();
    }

    virtual const Address& getRemoteAddress() {
        return delegate->getRemoteAddress();
    }

    virtual bool isOk() {
        return delegate->isOk();
    }

    virtual void reset() {
        delegate->reset();
    }

    virtual void close() {
        delegate->close();
    }

    virtual void beginPacket() {
        twiddlerReader.reset();
        delegate->beginPacket();
    }

    virtual void endPacket() {
        delegate->endPacket();
    }

    virtual void write(const Bytes& b);

    virtual int read(const Bytes& b);

    virtual void interrupt() { 
        delegate->getInputStream().interrupt();
    }

    void updateKind(const char *kind);

    static std::string rosToKind(const char *rosname);
};

#endif
