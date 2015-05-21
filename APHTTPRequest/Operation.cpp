//
//  Operation.cpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 06/05/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#include "Operation.hpp"
#include <iostream>

AP::Operation::Operation()  : _state(), _thread(nullptr) {
}

AP::Operation::~Operation() {
    cout << "Operation destructor" << endl;
    waitUntilFinish();
}

void AP::Operation::execute() {
    mainAsynchronous();
    didFinish();
}

void AP::Operation::start() {
    willStart();
    _thread = new thread(&Operation::execute, this);
}

void AP::Operation::startSynchronous() {
    willStart();
    mainSynchronous();
    didFinish();
}

void AP::Operation::cancel() {
    lock_guard<recursive_mutex> locker(_mutex);
    if ( isExecuting() && !isCancelled() ) {
        setCancelled(true);
    }
}

void AP::Operation::waitUntilFinish() {
    if ( _thread ) {
        _thread->join();
        delete _thread;
        _thread = nullptr;
    }
}

void AP::Operation::willStart() {
    lock_guard<recursive_mutex> locker(_mutex);
    setExecuting(true);
    setFinished(false);
    setCancelled(false);
}

void AP::Operation::didFinish() {
    lock_guard<recursive_mutex> locker(_mutex);
    setExecuting(false);
    setFinished(true);
}

void AP::Operation::setExecuting(bool executing) {
    lock_guard<recursive_mutex> locker(_mutex);
    _state.isExecuting = executing;
}

void AP::Operation::setFinished(bool finished) {
    lock_guard<recursive_mutex> locker(_mutex);
    _state.isFinished = finished;
}

void AP::Operation::setCancelled(bool cancelled) {
    lock_guard<recursive_mutex> locker(_mutex);
    _state.isCancelled = cancelled;
}

bool AP::Operation::isExecuting() {
    lock_guard<recursive_mutex> locker(_mutex);
    return _state.isExecuting;
}

bool AP::Operation::isFinished() {
    lock_guard<recursive_mutex> locker(_mutex);
    return _state.isFinished;
}

bool AP::Operation::isCancelled() {
    lock_guard<recursive_mutex> locker(_mutex);
    return _state.isCancelled;
}