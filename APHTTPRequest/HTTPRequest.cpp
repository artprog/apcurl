//
//  HTTPRequest.cpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 24/04/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#include "HTTPRequest.hpp"
#include <iostream>
#include <regex>

AP::HTTPRequest::HTTPRequest::HTTPRequest() : _httpHeadersList(NULL), _httpMethod(HTTPMethodGET) {
    _curl = curl_easy_init();
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, &HTTPRequest::writeCallback);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_content);
    curl_easy_setopt(_curl, CURLOPT_HEADERFUNCTION, &HTTPRequest::headerCallback);
    curl_easy_setopt(_curl, CURLOPT_HEADERDATA, &_response);
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, _httpHeadersList);
    _curl_multi = curl_multi_init();
}

AP::HTTPRequest::HTTPRequest::HTTPRequest(const string &url) : HTTPRequest() {
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
}

AP::HTTPRequest::HTTPRequest::~HTTPRequest() {
    waitUntilFinish();
    curl_multi_remove_handle(_curl_multi, _curl);
    curl_easy_cleanup(_curl);
    curl_multi_cleanup(_curl_multi);
    cout << "HTTPRequest destructor" << endl;
}

size_t AP::HTTPRequest::HTTPRequest::writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t bytes = size * nmemb;
    static_cast<string *>(userp)->append(static_cast<char *>(contents), bytes);
    return bytes;
}

size_t AP::HTTPRequest::HTTPRequest::headerCallback(char *buffer, size_t size, size_t nitems, void *userdata) {
    size_t bytes = size * nitems;
    string str;
    str.append(buffer, bytes);
    regex rgx("([^:]*)(?:: ?(.*))");
    smatch matches;
    if (regex_search(str, matches, rgx)) {
        if ( matches.size() == 3 ) {
            HTTPResponse *httpResponse = static_cast<HTTPResponse *>(userdata);
            httpResponse->setValueForHTTPHeaderField(matches[2], matches[1]);
        }
    }
    return bytes;
}

void AP::HTTPRequest::HTTPRequest::setValueForHTTPHeader(const string &value, const string &header) {
    string httpHeader = header + ": " + value;
    curl_slist_append(_httpHeadersList, httpHeader.c_str());
}

const AP::HTTPRequest::HTTPResponse& AP::HTTPRequest::HTTPRequest::execute() {
    startSynchronous();
    return _response;
}

void AP::HTTPRequest::HTTPRequest::execute(const function<void (const HTTPResponse &)> &handler) {
    _completionHandler = handler;
    start();
}

void AP::HTTPRequest::HTTPRequest::mainAsynchronous() {
    curl_multi_add_handle(_curl_multi, _curl);
    _content.clear();
    int count;
    do {
        curl_multi_perform(_curl_multi, &count);
    } while ( count > 0 || isCancelled() );
    if ( !isCancelled() ) {
        long code = 0;
        curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &code);
        _response.setCode(code);
    }
    _response.setResponseBody(_content);
    curl_multi_remove_handle(_curl_multi, _curl);
}

void AP::HTTPRequest::HTTPRequest::mainSynchronous() {
    _content.clear();
    curl_easy_perform(_curl);
    long code = 0;
    curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &code);
    _response.setCode(code);
    _response.setResponseBody(_content);
}

void AP::HTTPRequest::HTTPRequest::didFinish() {
    Operation::didFinish();
    if ( _completionHandler ) {
        _completionHandler(_response);
    }
}