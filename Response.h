#ifndef __Response_h_
#define __Response_h_

#include <map>
#include <string>
#include <sstream>

#include <MySocket/Socket.h>

using namespace std;

typedef Socket Channel;

typedef map<string, string> Headers;

class Response {
public:
	Response(Channel *channel, int statusCode = 200);

	virtual ~Response();

	void write(const string &str = "", const string &type = "", const Headers &headers = Headers(), int status = 0);

	void forward(const string &location);

	void redirect(const string &location);

	void begin(const string &type, const Headers &headers = Headers());

	void chunk(const string &payload);

	void end();

private:
	string mType;
	Channel *mChannel;
	int mStatusCode;
	
	map<int, string> mStatusMessage;



	void bareWrite(const string &str, const Headers &headers, int status);
};

#endif

