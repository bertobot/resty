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
	mRequestMap["DELETE"][path] = f;
}

void Resty::HEAD(const string &path, MethodHandler f) {
	mRequestMap["HEAD"][path] = f;
}

void Resty::GET(const string &path, MethodHandler f) {
	mRequestMap["GET"][path] = f;
}

void Resty::POST(const string &path, MethodHandler f) {
	mRequestMap["POST"][path] = f;
}

void Resty::PUT(const string &path, MethodHandler f) {
	mRequestMap["PUT"][path] = f;
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

