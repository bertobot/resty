#include "Response.h"

Response::Response(Channel *channel, int statusCode) {
	mChannel = channel;
	mStatusCode = statusCode;

	// TODO: move this out
	mStatusMessage[100] = "Continue";

	mStatusMessage[200] = "OK";

	mStatusMessage[301] = "Moved";
	mStatusMessage[302] = "Found";
	mStatusMessage[304] = "Not Modified";

	mStatusMessage[400] = "Bad Request";
	mStatusMessage[401] = "Authorization Required";
	mStatusMessage[403] = "Forbidden";
	mStatusMessage[404] = "Not Found";
	mStatusMessage[413] = "Request Entity Too Large";
	mStatusMessage[415] = "Unsupported Media Type";

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

	bareWrite(str.c_str(), str.length(), h, status);
}

void Response::write(const char *data, size_t len, const string &type, const Headers &headers, int status) {

	Headers h(headers);

	stringstream ss;

	ss << len;

	h["Content-Length"] = ss.str();

	if (! type.empty() )
		h["Content-Type"] = type;

	bareWrite(data, len, h, status);
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

	bareWrite("", 0, h, 200);
}

void Response::chunk(const string &payload, bool finished) {
	if (mChannel) {
		stringstream ss;

		ss << hex << payload.size() << "\r\n" << payload;

		mChannel->writeLine(ss.str() );

		if (finished)
			mChannel->writeLine("0\r\n");
	}
}

void Response::end() {
	if (mChannel) 
		mChannel->writeLine("0\r\n");
}

void Response::bareWrite(const char *data, size_t len, const Headers &headers, int status) {
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

		mChannel->write(ss.str());

		mChannel->write(data, len);
	}
}

void Response::renderFile(const string &type, const string &filename) {
	FILE *file = fopen(filename.c_str(), "r");

	if (! file) {
		mStatusCode = 500;
		write();
		throw Exception("couldn't open file");
	}

	char *buffer = new char[8192];

	long int read = 0;

	begin(type);

	while (true) {
		bzero(buffer, 8192);

		read = fread(buffer, 8192, 1, file);

		chunk(buffer);

		if (read < 8192)
			break;
	}

	end();

	delete [] buffer;

	delete file;

	file = NULL;
}

void Response::ok(const string &str, const string &type, const Headers &headers) {
    write(str, type, headers, 200);
}

void Response::created(const string &str, const string &type, const Headers &headers) {
    write(str, type, headers, 201);
}

void Response::accepted(const string &str, const string &type, const Headers &headers) {
    write(str, type, headers, 202);
}

void Response::badRequest(const string &str, const string &type, const Headers &headers) {
    write(str, type, headers, 400);
}

void Response::notFound(const string &str, const string &type, const Headers &headers) {
    write(str, type, headers, 404);
}

void Response::internalServerError(const string &str, const string &type, const Headers &headers) {
    write(str, type, headers, 500);
}

void Response::_continue(const string &str, const string &type, const Headers &headers) {
    write(str, type, headers, 100);
}

void Response::requestEntityTooLarge(const string &str, const string &type, const Headers &headers) {
    write(str, type, headers, 413);
}

void Response::unsupportedMediaType(const string &str, const string &type, const Headers &headers) {
    write(str, type, headers, 415);
}

