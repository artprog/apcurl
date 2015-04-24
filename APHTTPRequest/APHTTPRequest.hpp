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

class APHTTPRequest {
    CURL *_curl;
  public:
    APHTTPRequest() { _curl = curl_easy_init(); }
    ~APHTTPRequest() { curl_easy_cleanup(_curl); }
};

#endif /* defined(__APHTTPRequest__APHTTPRequest__) */
