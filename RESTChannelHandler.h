#ifndef __RESTChannelHandler_h_
#define __RESTChannelHandler_h_

#include <netty++/ChannelHandler.h>

#include "Request.h"
#include "Response.h"

using namespace std;

typedef void (*MethodHandler)(const Request&, Response&);
typedef std::map<std::string, MethodHandler> pathfunc;
typedef std::map<std::string, pathfunc> RequestMap;

class RESTChannelHandler : public ChannelHandler {
public:

	RESTChannelHandler(RequestMap *requestmap) { mRequestMap = requestmap; }

	virtual ~RESTChannelHandler() { mRequestMap = NULL; }

	void onMessageReceived(Channel &channel);

	/*
	void onException();

	void onStart(Channel &channel);

	bool shutdownOnExit(Channel &channel) { return false; }
	*/

private:
	RequestMap *mRequestMap;
	
	
};

#endif

