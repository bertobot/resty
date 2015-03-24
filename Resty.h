#ifndef __Resty_h_
#define __Resty_h_

#include "RESTChannelHandler.h"
#include <netty++/Server.h>

class Resty {
public:
	Resty(int port, int workers=1);

	virtual ~Resty();



	void DELETE(const string &path, MethodHandler f);

	void GET(const string &path, MethodHandler f);

	void HEAD(const string &path, MethodHandler f);

	void POST(const string &path, MethodHandler f);

	void PUT(const string &path, MethodHandler f);

    void run();

    void start();

    void stop();

private:
    RequestMap mRequestMap;

    RESTChannelHandler *mRCH;

    Server *mServer;

    RequestEnvelop parsePath(const string &path, MethodHandler f);

    void prep(const string &method, const string &path, MethodHandler f);
};

#endif

// vim: ts=4:sw=4:expandtab

