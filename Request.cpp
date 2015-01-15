#include "Request.h"

Request::Request(string &payload) {
    
    // mMethods = { "DELETE", "GET", "HEAD", "POST", "PUT" };
    
    SplitIterator bchannel(payload);

    string input = bchannel.readLine();

    vector<string> tokens = split(' ', input);

    // TODO: validate request line
    // [ method | path | protocol | / | version ]

    // this is validation
    /*
    if (mMethods.find(tokens[0]) == mMethods.end() )
        throw Exception(string("invalid method: ") + tokens[0] );
    */

    method  = tokens[0];

    rawPath = tokens[1];

    vector<string> tokens2 = split('/', tokens[2]);

    protocol    = tokens2[0];

    version     = atof(tokens2[1].c_str() );

    // parse out relative path and query

    SplitIterator si(tokens[1], "?");

    path = si.next();

    query = si.rest();

    parseParameters(query);

    

    // TODO: validate version
    // TODO: validate all 



    // process headers
    while (true) {
        input = bchannel.readLine();

        // debug
        //cout << "[d] " << input << endl;

        deWhiteSpace(input);

        if (input.empty())
            break;

        size_t pos = input.find(':');

        if (pos == string::npos)
            continue;

        headers[input.substr(0, pos)] = input.substr(pos + 2);

    } 

    // process body

    // TODO: validate Content-Length
    body = bchannel.read(atoi(headers["Content-Length"].c_str()));

    parseParameters(body);
}

string Request::getParameter(const string &key) const {
    map<string, string>::const_iterator itr = parameters.find(key);

    if (itr != parameters.end() )
        return itr->second;
    return string();
}

void Request::parseParameters(const string &str) {
    vector<string> tokens = split('&', str);

    for (unsigned int i = 0; i < tokens.size(); i++) {
        size_t pos = tokens[i].find('=');

        if (pos == string::npos)
            continue;

        parameters[tokens[i].substr(0, pos)] = tokens[i].substr(pos + 1);
    }
}

// vim: ts=4:sw=4:expandtab

