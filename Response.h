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

	void write(const char *data, size_t len, const string &type = "", const Headers &headers = Headers(), int status = 0);

	void forward(const string &location);

	void redirect(const string &location);

	void begin(const string &type, const Headers &headers = Headers());

	void chunk(const string &payload, bool finished = false);

	void end();

	void renderFile(const string &type, const string &filename);

    // convenience wrappers
    // TODO: add others
    void Ok(const string &str="", const string &type="", const Headers &headers=Headers());
    void Created(const string &str="", const string &type="", const Headers &headers=Headers());
    void Accepted(const string &str="", const string &type="", const Headers &headers=Headers());
    void BadRequest(const string &str="", const string &type="", const Headers &headers=Headers());
    void NotFound(const string &str="", const string &type="", const Headers &headers=Headers());
    void InternalServerError(const string &str="", const string &type="", const Headers &headers=Headers());

private:
	string mType;
	Channel *mChannel;
	int mStatusCode;
	
	map<int, string> mStatusMessage;


	void bareWrite(const char *data, size_t len, const Headers &headers, int status);
};

#endif

