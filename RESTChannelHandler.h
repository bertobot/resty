#ifndef __RESTChannelHandler_h_
#define __RESTChannelHandler_h_

#include <vector>
#include <boost/regex.hpp>

#include <netty++/ChannelHandler.h>

#include "Request.h"
#include "Response.h"


using namespace std;

typedef void (*MethodHandler)(const Request&, Response&);

struct RequestEnvelop {

    MethodHandler func;
    boost::regex pathre;
    vector<string> names;

    RequestEnvelop() {}

    RequestEnvelop(MethodHandler f, const boost::regex &p, const vector<string> &n) {
        func = f;
        pathre = p;
        names = n;
    }
};

//typedef std::map<std::string, MethodHandler> pathfunc;

typedef map<string, vector<RequestEnvelop> > RequestMap;

class RESTChannelHandler : public ChannelHandler {
public:

	RESTChannelHandler(RequestMap *requestmap) { mRequestMap = requestmap; }

	virtual ~RESTChannelHandler() { mRequestMap = NULL; }

	void onMessageReceived(Channel &channel, std::string &payload);

	/*
	void onException();

	void onStart(Channel &channel);

	bool shutdownOnExit(Channel &channel) { return false; }
	*/

private:
	RequestMap *mRequestMap;
	
	
};

#endif

// vim: ts=4:sw=4:expandtab
