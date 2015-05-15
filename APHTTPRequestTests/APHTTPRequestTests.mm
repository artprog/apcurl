//
//  APHTTPRequestTests.m
//  APHTTPRequestTests
//
//  Created by Adam Zugaj on 15/05/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#import "APHTTPRequest.hpp"
#include <string>

using namespace std;

@interface APHTTPRequestTests : XCTestCase

@end

@implementation APHTTPRequestTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testSynchronous {
    NSURL *url = [[NSBundle bundleForClass:[self class]] URLForResource:@"artprog" withExtension:@"html"];
    NSString *content = [NSString stringWithContentsOfURL:url encoding:NSUTF8StringEncoding error:NULL];
    string contentString([content cStringUsingEncoding:NSUTF8StringEncoding]);
    APHTTPRequest request([[url absoluteString] cStringUsingEncoding:NSUTF8StringEncoding]);
    string response = request.execute();
    XCTAssert(response == contentString, @"wrong request response!");
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
