#include "Request.h"

Request::Request(Channel &channel) {
    
    // mMethods = { "DELETE", "GET", "HEAD", "POST", "PUT" };
    
    string input = channel.readLine();

    vector<string> tokens = split(' ', input);

    // TODO: validate request line
    // [ method | path | protocol | / | version ]

    // this is validation
    /*
    if (mMethods.find(tokens[0]) == mMethods.end() )
        throw Exception(string("invalid method: ") + tokens[0] );
    */

    method  = tokens[0];

    path    = tokens[1];
    
    vector<string> tokens2 = split('/', tokens[2]);

    protocol    = tokens2[0];

    version     = atof(tokens2[1].c_str() );

    // TODO: validate version
    // TODO: validate all 



    // process headers
    while (true) {
        input = channel.readLine();

        // debug
        //cout << "[d] " << input << endl;

        deWhiteSpace(input);

        if (input.empty())
            break;

        int pos = 0;

        if (pos = input.find(": ") == string::npos)
            continue;

        headers[input.substr(0, pos)] = input.substr(pos + 1);

    } 

    // process body

    // TODO: validate Content-Length
    body = channel.read(atoi(headers["Content-Length"].c_str()));
}

// vim: ts=4:sw=4:expandtab

