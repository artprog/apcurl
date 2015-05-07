//
//  APOperation.cpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 06/05/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#include "APOperation.hpp"
#include <iostream>

APOperation::APOperation()  : _state(), _thread(nullptr) {
}

APOperation::~APOperation() {
    cout << "APOperation destructor" << endl;
    waitUntilFinish();
}

void APOperation::execute() {
    mainAsynchronous();
    didFinish();
}

void APOperation::start() {
    willStart();
    _thread = new thread(&APOperation::execute, this);
}

void APOperation::startSynchronous() {
    willStart();
    mainSynchronous();
    didFinish();
}

void APOperation::cancel() {
    lock_guard<recursive_mutex> locker(_mutex);
    if ( isExecuting() && !isCancelled() ) {
        setCancelled(true);
    }
}

void APOperation::waitUntilFinish() {
    if ( _thread ) {
        _thread->join();
        delete _thread;
        _thread = nullptr;
    }
}

void APOperation::willStart() {
    lock_guard<recursive_mutex> locker(_mutex);
    setExecuting(true);
    setFinished(false);
    setCancelled(false);
}

void APOperation::didFinish() {
    lock_guard<recursive_mutex> locker(_mutex);
    setExecuting(false);
    setFinished(true);
}

void APOperation::setExecuting(bool executing) {
    lock_guard<recursive_mutex> locker(_mutex);
    _state.isExecuting = executing;
}

void APOperation::setFinished(bool finished) {
    lock_guard<recursive_mutex> locker(_mutex);
    _state.isFinished = finished;
}

void APOperation::setCancelled(bool cancelled) {
    lock_guard<recursive_mutex> locker(_mutex);
    _state.isCancelled = cancelled;
}

bool APOperation::isExecuting() {
    lock_guard<recursive_mutex> locker(_mutex);
    return _state.isExecuting;
}

bool APOperation::isFinished() {
    lock_guard<recursive_mutex> locker(_mutex);
    return _state.isFinished;
}

bool APOperation::isCancelled() {
    lock_guard<recursive_mutex> locker(_mutex);
    return _state.isCancelled;
}