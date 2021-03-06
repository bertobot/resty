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
    Request(string &payload, Channel &channel);

    virtual ~Request() { }

    //void getParameters() const;

    string getParameter(const string &key) const;

    void setParameter(const string &key, const string &value);

    string getHeader(const string &key) const;

// private:
    string method;

    string path;

    string rawPath;

    string query;

    string protocol;
    
    float version;


    map<string, string> headers;

    string body;

    set<string> mMethods;

private:
    map<string, string> parameters;

    void parseParameters(const string &str);
};

#endif

// vim: ts=4:sw=4:expandtab

