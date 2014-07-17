#include "Response.h"

Response::Response(Channel *channel, int statusCode) {
	mChannel = channel;
	mStatusCode = statusCode;

	// TODO: move this out
	mStatusMessage[200] = "OK";

	mStatusMessage[301] = "Moved";
	mStatusMessage[302] = "Found";
	mStatusMessage[304] = "Not Modified";

	mStatusMessage[400] = "Bad Request";
	mStatusMessage[401] = "Authorization Required";
	mStatusMessage[403] = "Forbidden";
	mStatusMessage[404] = "Not Found";

	mStatusMessage[500] = "Internal Error";
	mStatusMessage[501] = "Not Implemented";
}

Response::~Response() {
	mChannel = NULL;
}

void Response::write(const string &str, const string &type, const Headers &headers, int status) {
	if (status == 0)
		status = mStatusCode;

	Headers h = headers;

	stringstream cl;

	cl << str.length();

	h["Content-Length"] = cl.str();

	if (! type.empty() )
		h["Content-Type"] = type;

	if (mChannel) {
		stringstream ss;
		ss << "HTTP/1.1 " << mStatusCode << " " << mStatusMessage[mStatusCode] << endl;


		// print h
		Headers::iterator itr = h.begin();

		for(; itr != h.end(); itr++) {
			if (itr->second.empty() )
				continue;

			ss << itr->first << ": " << itr->second << endl;
		}

		ss << "\r\n";

		ss << str;

		mChannel->write(ss.str());
	}
}

void Response::forward(const string &location) {
	Headers h;
	h["Location"] = location;

	write("", "", h, 301);
}

void Response::redirect(const string &location) {
	Headers h;
	h["Location"] = location;

	write("", "", h, 302);
}


