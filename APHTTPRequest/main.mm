//
//  main.m
//  APHTTPRequest
//
//  Created by Adam Zugaj on 24/04/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#include <iostream>
#include "HTTPRequest.hpp"

using namespace std;
using namespace AP::HTTPRequest;

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        HTTPRequest request("http://artprog.pl");
        cout << request << endl << request << endl;
        request.execute([](const HTTPResponse &response) {
            cout << response.responseBody() << endl;
        });
        cout << "I am here" << endl;
    }
    return 0;
}
