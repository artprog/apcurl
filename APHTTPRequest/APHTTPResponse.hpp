//
//  APHTTPResponse.hpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 08/05/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#ifndef __APHTTPRequest__APHTTPResponse__
#define __APHTTPRequest__APHTTPResponse__

#include <map>
#include <string>

using namespace std;

class APHTTPResponse {
    map<string, string> _responseHeaders;
    string _responseBody;
  public:
    string responseBody() const { return _responseBody; }
    void setValueForHTTPHeaderField(const string &value, const string &field);
    string valueForHTTPHeaderField(const string &field);
};

#endif /* defined(__APHTTPRequest__APHTTPResponse__) */
