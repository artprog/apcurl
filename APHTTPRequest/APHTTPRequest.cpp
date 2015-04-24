//
//  APHTTPRequest.cpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 24/04/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#include "APHTTPRequest.hpp"

APHTTPRequest::APHTTPRequest() {
    _curl = curl_easy_init();
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, &APHTTPRequest::writeCallback);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_content);
}

size_t APHTTPRequest::writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t bytes = size * nmemb;
    static_cast<string *>(userp)->append(static_cast<char *>(contents), bytes);
    return bytes;
}

const string& APHTTPRequest::execute() {
    _content.clear();
    curl_easy_perform(_curl);
    return _content;
}