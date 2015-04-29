//
//  APHTTPRequest.cpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 24/04/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#include "APHTTPRequest.hpp"
//#include <thread>

APHTTPRequest::APHTTPRequest() {
    _curl = curl_easy_init();
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, &APHTTPRequest::writeCallback);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_content);
    _curl_multi = curl_multi_init();
    curl_multi_add_handle(_curl_multi, _curl);
}

APHTTPRequest::APHTTPRequest(const string &url) : APHTTPRequest() {
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
}

APHTTPRequest::~APHTTPRequest() {
    curl_multi_remove_handle(_curl_multi, _curl);
    curl_easy_cleanup(_curl);
    curl_multi_cleanup(_curl_multi);
}

size_t APHTTPRequest::writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t bytes = size * nmemb;
    static_cast<string *>(userp)->append(static_cast<char *>(contents), bytes);
    return bytes;
}

//void APHTTPRequest::executeBackground() {
//    int count;
//    do {
//        curl_multi_perform(_curl_multi, &count);
//    } while ( count > 0 );
//    handler(_content);
//}

const string& APHTTPRequest::execute() {
    _content.clear();
    curl_easy_perform(_curl);
    return _content;
}

void APHTTPRequest::execute(const function<void (const string &)> &handler) {
//    thread t(&APHTTPRequest::executeBackground);
//    t.join();
    int count;
    do {
        curl_multi_perform(_curl_multi, &count);
    } while ( count > 0 );
    handler(_content);
}