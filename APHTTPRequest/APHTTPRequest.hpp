//
//  APHTTPRequest.hpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 24/04/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#ifndef __APHTTPRequest__APHTTPRequest__
#define __APHTTPRequest__APHTTPRequest__

#include <curl/curl.h>
#include <string>
#include <functional>
#include "APOperation.hpp"
#include "APHTTPResponse.hpp"

using namespace std;

class APHTTPRequest : public APOperation {
    CURL *_curl;
    CURLM *_curl_multi;
    string _content;
    APHTTPResponse _response;
    function<void (const string &)> _completionHandler;
  private:
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
    static size_t headerCallback(char *buffer, size_t size, size_t nitems, void *userdata);
  protected:
    void mainAsynchronous();
    void mainSynchronous();
    void didFinish();
  public:
    APHTTPRequest();
    APHTTPRequest(const string &url);
    ~APHTTPRequest();
    const string& execute();
    void execute(const function<void (const string &)> &handler);
};

static ostream& operator<<(ostream& stream, APHTTPRequest &request) {
    stream << request.execute();
    return stream;
}

#endif /* defined(__APHTTPRequest__APHTTPRequest__) */
