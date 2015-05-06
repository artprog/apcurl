//
//  APOperation.cpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 06/05/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#include "APOperation.hpp"
#include <iostream>

APOperation::APOperation()  : _isExecuting(false), _isFinished(false),
    _isCancelled(false), _thread(nullptr) {
}

APOperation::~APOperation() {
    cout << "APOperation destructor" << endl;
    waitUntilFinish();
}

void APOperation::execute() {
    main();
    didFinish();
}

void APOperation::start() {
    _thread = new thread(&APOperation::execute, this);
}

void APOperation::startSynchronous() {
    execute();
}

void APOperation::cancel() {
}

void APOperation::waitUntilFinish() {
    if ( _thread ) {
        _thread->join();
        delete _thread;
        _thread = nullptr;
    }
}

void APOperation::didFinish() {
    _isExecuting = false;
    _isCancelled = false;
    _isFinished = true;
}