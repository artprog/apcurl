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
#include "Operation.hpp"
#include "HTTPResponse.hpp"

using namespace std;

namespace AP {

class HTTPRequest : public Operation {
    CURL *_curl;
    CURLM *_curl_multi;
    string _content;
    HTTPResponse _response;
    function<void (const string &)> _completionHandler;
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
    const string& execute();
    void execute(const function<void (const string &)> &handler);
};

static ostream& operator<<(ostream& stream, HTTPRequest &request) {
    stream << request.execute();
    return stream;
}
    
}

#endif /* defined(__HTTPRequest__HTTPRequest__) */
