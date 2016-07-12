//
//  HTTPResponse.hpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 08/05/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#ifndef __HTTPRequest__HTTPResponse__
#define __HTTPRequest__HTTPResponse__

#include <map>
#include <string>

using namespace std;

namespace AP {
namespace HTTPRequest {

class HTTPResponse {
    long _code;
    string _responseBody;
    map<string, string> _responseHeaders;
  public:
    HTTPResponse() : _code(0) { }
    void setCode(long code) { _code = code; }
    long code() const { return _code; }
    void setResponseBody(const string &body) { _responseBody = body; }
    const string& responseBody() const { return _responseBody; }
    void setValueForHTTPHeaderField(const string &value, const string &field);
    string valueForHTTPHeaderField(const string &field);
};

}
}

#endif /* defined(__HTTPRequest__HTTPResponse__) */
