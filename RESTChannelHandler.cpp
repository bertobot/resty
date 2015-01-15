#include "RESTChannelHandler.h"

void RESTChannelHandler::onMessageReceived(Channel &channel, std::string &payload) {

    try {
        Request request(payload);

        if ((*mRequestMap)[request.method][request.path]) {
            Response res(&channel);

            MethodHandler f;

            f  = (*mRequestMap)[request.method][request.path];

            f(request, res);

            //&((*mRequestMap)[request.method][request.path])(request, res);
        }
        

        else {
            Response fof(&channel, 404);
            fof.write();
        }

    }
    catch(Exception e) {
        Response five(&channel, 500);
        five.write();
    }

    // done.  close connection
    channel.close();
}

// vim: ts=4:sw=4:expandtab

