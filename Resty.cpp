#include "Resty.h"

Resty::Resty(int port, int workers)  {
	mRCH = new RESTChannelHandler(&mRequestMap);

	mServer = new Server(port, workers, mRCH);
}

Resty::~Resty() {
	delete mServer; mServer = NULL;
	delete mRCH; mRCH = NULL;
}

void Resty::DELETE(const string &path, MethodHandler f) {
    prep("DELETE", path, f);
}

void Resty::HEAD(const string &path, MethodHandler f) {
    prep("HEAD", path, f);
}

void Resty::GET(const string &path, MethodHandler f) {
    prep("GET", path, f);
}

void Resty::POST(const string &path, MethodHandler f) {
    prep("POST", path, f);
}

void Resty::PUT(const string &path, MethodHandler f) {
    prep("PUT", path, f);
}

void Resty::run() {
	mServer->run();
}

void Resty::start() {
	mServer->start();
}

void Resty::stop() {
	mServer->stop();
}

RequestEnvelop Resty::parsePath(const string &path, MethodHandler f) {

    RequestEnvelop result;

    string mpath = path;

    boost::match_results<std::string::const_iterator> capture;

    boost::regex re("(:(\\w+))");

    while (regex_search(mpath, capture, re) ) {
        string match = capture[1];

        result.names.push_back(capture[2]);

        size_t found = mpath.find(match);

        if (found != string::npos)
            mpath.replace(found, match.size(), "(\\w+)");
    }

    result.pathre = boost::regex(mpath);

    result.func = f;

    return result;
}

void Resty::prep(const string &method, const string &path, MethodHandler f) {
    string mpath = path;

    vector<string> names;

	mRequestMap[method].push_back(parsePath(mpath, f) );
}

// vim: ts=4:sw=4:expandtab
