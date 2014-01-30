// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2013 iCub Facility
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <stdio.h>
#include <stdlib.h>
#include <yarp/os/all.h>

using namespace yarp::os;

int main(int argc, char *argv[]) {
    Network yarp;
    RpcServer server;

    server.promiseType(Type::byNameOnWire("rospy_tutorials/AddTwoInts"));

    if (!server.open("/add_two_ints@/yarp_add_int_server")) {
        fprintf(stderr,"Failed to open port\n");
        return 1;
    }

    while (true) {
        Bottle msg, reply;
        server.read(msg,true);
        int x = msg.get(0).asInt();
        int y = msg.get(1).asInt();
        int sum = x + y;
        reply.addInt(sum);
        printf("Got %d + %d, answering %d\n", x, y, sum);
        server.reply(reply);
    }

    return 0;
}
