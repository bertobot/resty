#include "RESTChannelHandler.h"

void RESTChannelHandler::onMessageReceived(Channel &channel, std::string &payload) {

    try {
        Request request(payload);

        bool done = false;

        boost::match_results<string::const_iterator> capture;

        for (unsigned int i = 0; i < (*mRequestMap)[request.method].size(); i++) {

            if (regex_search(request.path, capture, (*mRequestMap)[request.method][i].pathre) ) {

                // push all matches into parameters.

                for (unsigned int j = 0; j < (*mRequestMap)[request.method][i].names.size(); j++)
                    request.setParameter((*mRequestMap)[request.method][i].names[j], capture[j+1]);


                Response res(&channel);

                MethodHandler f;

                f = (*mRequestMap)[request.method][i].func;

                f(request, res);
             
                done = true;

                break;

            }
        }

        if (! done) {
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

