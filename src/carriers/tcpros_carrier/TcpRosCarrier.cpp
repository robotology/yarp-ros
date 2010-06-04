// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "TcpRosCarrier.h"
#include "RosHeader.h"

#include <string>
#include <map>

#include <yarp/os/Bytes.h>
#include <yarp/os/impl/NetType.h>
#include <yarp/os/impl/Name.h>

using namespace yarp::os::impl;
using namespace yarp::os;
using namespace std;

bool TcpRosCarrier::checkHeader(const Bytes& header) {
    if (header.length()!=8) {
        return false;
    }
    Bytes h1(header.get(),4);
    Bytes h2(header.get()+4,4);
    headerLen1 = NetType::netInt(h1);
    headerLen2 = NetType::netInt(h2);
    printf("tcpros? %d %d\n", headerLen1,headerLen2);
    if (headerLen1<60000&&headerLen1>=0 &&
        headerLen2<60000&&headerLen2>=0) {
        // plausible I guess, and no real choice
        printf("ok, tcpros\n");
        return true;
    }
    return false;
}


bool TcpRosCarrier::sendHeader(Protocol& proto) {
    printf("Route is %s\n", proto.getRoute().toString().c_str());
    Name n(proto.getRoute().getCarrierName() + "://test");
    String mode = "topic";
    String modeValue = n.getCarrierModifier("topic");
    if (modeValue=="") {
        mode = "service";
        modeValue = n.getCarrierModifier("service");
    }
    if (modeValue=="") {
        printf("need to be a service or topic, this will break\n");
    }

    RosHeader header;
    printf("Writing to %s\n", proto.getStreams().getRemoteAddress().toString().c_str()); 
    printf("Writing from %s\n", proto.getStreams().getLocalAddress().toString().c_str());
    //header.data["type"] = "std_msgs/String";
    header.data[mode.c_str()] = modeValue.c_str();
    header.data["md5sum"] = "*";
    header.data["callerid"] = "/not/valid/at/all/i/am/afraid/old/chum";
    string header_serial = header.writeHeader();
    string header_len(4,'\0');
    char *at = (char*)header_len.c_str();
    RosHeader::appendInt(at,header_serial.length());
    printf("Writing %s -- %d bytes\n", 
           RosHeader::showMessage(header_len).c_str(),
           header_len.length());
    
    Bytes b1((char*)header_len.c_str(),header_len.length());
    proto.os().write(b1);
    printf("Writing %s -- %d bytes\n", 
           RosHeader::showMessage(header_serial).c_str(),
           header_serial.length());
    Bytes b2((char*)header_serial.c_str(),header_serial.length());
    proto.os().write(b2);

    return proto.os().isOk();
}


bool TcpRosCarrier::expectReplyToHeader(Protocol& proto) {
    RosHeader header;

    char mlen[4];
    Bytes mlen_buf(mlen,4);
    
    int res = NetType::readFull(proto.is(),mlen_buf);
    if (res<4) {
        printf("Fail %s %d\n", __FILE__, __LINE__);
        return false;
    }
    int len = NetType::netInt(mlen_buf);
    printf("Len %d\n", len);
    if (len>10000) {
        printf("not ready for serious messages\n");
        return false;
    }
    ManagedBytes m(len);
    res = NetType::readFull(proto.is(),m.bytes());
    if (res!=len) {
        printf("Fail %s %d\n", __FILE__, __LINE__);
        return false;
    }
    header.readHeader(string(m.get(),m.length()));

    // we are a pull stream
    sender = false;
    TcpRosStream *stream = new TcpRosStream(proto.giveStreams(),sender);
    if (stream==NULL) { return false; }
    proto.takeStreams(stream);
    printf("tcpros carrier not implemented yet\n");        
    
    return proto.is().isOk();
}
    
bool TcpRosCarrier::expectSenderSpecifier(Protocol& proto) {
    proto.setRoute(proto.getRoute().addFromName("tcpros"));
    return true;
}

bool TcpRosCarrier::write(Protocol& proto, SizedWriter& writer) {

    // For now, we will require objects being written to be either:
    //   + raw data
    //   + raw data, with a Bottle compatible blob header.

    if (writer.length()<1) {
        fprintf(stderr,"tcpros_carrier given no data");
        return false;
    }
    
    int total_len = 0;
    for (int i=0; i<writer.length(); i++) {
        total_len += writer.length(i);
    }
    bool has_header = false;
    int payload_index = 0;
    int payload_offset = 0;
    int remaining = total_len;
    if (writer.length(0)>=12) {
        // could this be a Bottle compatible blob?
        char *base = (char*)writer.data(0);
        Bytes b1(base,4);
        Bytes b2(base+4,4);
        Bytes b3(base+8,4);
        int i1 = NetType::netInt(b1);
        int i2 = NetType::netInt(b2);
        int i3 = NetType::netInt(b3);
        printf(">>> %d %d %d\n", i1, i2, i3);
        if (i1==BOTTLE_TAG_LIST+BOTTLE_TAG_BLOB) {
            if (i2==1) {
                if (i3==total_len - 12) {
                    // good enough
                    printf("Header detected\n");
                    has_header = true;
                    payload_index = 0;
                    payload_offset = 12;
                    remaining -= payload_offset;
                }
            }
        }
    }

    NetInt32 len_out = remaining;
    Bytes blen_out((char*)&len_out,sizeof(len_out));
    proto.os().write(blen_out);

    for (int i=payload_index; i<writer.length(); i++) {
        const char *data = writer.data(i);
        int len = writer.length(i);
        if (len>payload_offset) {
            Bytes b((char*)data+payload_offset,len-payload_offset);
            proto.os().write(b);
        }
        payload_offset = 0;
    }
    
    return proto.getStreams().isOk();
}

bool TcpRosCarrier::reply(Protocol& proto, SizedWriter& writer) {
    // don't need to do anything special for now.
    return proto.defaultReply(writer);
}
