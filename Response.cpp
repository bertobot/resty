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

	Headers h(headers);

	stringstream cl;

	cl << str.length();

	h["Content-Length"] = cl.str();

	if (! type.empty() )
		h["Content-Type"] = type;

	bareWrite(str, h, status);

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

void Response::begin(const string &type, const Headers &headers) {
	Headers h(headers);

	h["Transfer-Encoding"] = "chunked";

	bareWrite("", h, 200);
}

void Response::chunk(const string &payload) {
	if (mChannel) {
		stringstream ss;

		ss << hex << payload.size() << "\r\n" << payload;

		mChannel->writeLine(ss.str() );
	}
}

void Response::end() {
	if (mChannel) {
		mChannel->writeLine("0");
		mChannel->writeLine("");
	}
}

void Response::bareWrite(const string &str, const Headers &headers, int status) {
	Headers h(headers);

	if (status == 0)
		status = mStatusCode;

	if (mChannel) {
		stringstream ss;
		ss << "HTTP/1.1 " << status << " " << mStatusMessage[status] << endl;

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

