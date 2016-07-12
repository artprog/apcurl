//
//  HTTPRequest.hpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 24/04/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#ifndef __HTTPRequest__HTTPRequest__
#define __HTTPRequest__HTTPRequest__

#include <curl/curl.h>
#include <string>
#include <functional>
#include <map>
#include "Operation.hpp"
#include "HTTPResponse.hpp"
#include "HTTPRequestTypes.hpp"

using namespace std;

namespace AP {
namespace HTTPRequest {

class HTTPRequest : public Operation {
    CURL *_curl;
    CURLM *_curl_multi;
    struct curl_slist *_httpHeadersList;
    string _content;
    HTTPMethod _httpMethod;
    HTTPResponse _response;
    function<void (const HTTPResponse &)> _completionHandler;
  private:
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
    static size_t headerCallback(char *buffer, size_t size, size_t nitems, void *userdata);
  protected:
    void mainAsynchronous();
    void mainSynchronous();
    void didFinish();
  public:
    HTTPRequest();
    HTTPRequest(const string &url);
    ~HTTPRequest();
    inline void setHTTPMethod(HTTPMethod method) { _httpMethod = method; }
    HTTPMethod httpMethod() const { return _httpMethod; }
    void setValueForHTTPHeader(const string &value, const string &header);
    const HTTPResponse& execute();
    void execute(const function<void (const HTTPResponse &)> &handler);
};

static ostream& operator<<(ostream& stream, HTTPRequest &request) {
    stream << request.execute().responseBody();
    return stream;
}

}    
}

#endif /* defined(__HTTPRequest__HTTPRequest__) */
