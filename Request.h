#ifndef __Request_h_
#define __Request_h_

#include <MySocket/Socket.h>
#include <libstrmanip++/utils.h>

#include <map>
#include <set>
#include <string>
#include <vector>

typedef Socket Channel;

using namespace std;

class Request {
public:
    Request(Channel &channel);

    virtual ~Request() { }

// private:
    string method;

    string path;

    string protocol;
    
    float version;


    map<string, string> headers;

    string body;


    set<string> mMethods;
};

#endif

// vim: ts=4:sw=4:expandtab

