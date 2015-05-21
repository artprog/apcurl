//
//  HTTPResponse.cpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 08/05/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#include "HTTPResponse.hpp"

void AP::HTTPResponse::setValueForHTTPHeaderField(const string &value, const string &field) {
    _responseHeaders[field] = value;
}

string AP::HTTPResponse::valueForHTTPHeaderField(const string &field) {
    return _responseHeaders[field];
}