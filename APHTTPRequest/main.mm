//
//  main.m
//  APHTTPRequest
//
//  Created by Adam Zugaj on 24/04/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#include <iostream>
#include "APHTTPRequest.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        APHTTPRequest request("http://artprog.pl");
        cout << request << endl << request;
    }
    return 0;
}
