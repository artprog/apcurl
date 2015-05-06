//
//  APOperation.hpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 06/05/15.
//  Copyright (c) 2015 ArtProg. All rights reserved.
//

#ifndef __APHTTPRequest__APOperation__
#define __APHTTPRequest__APOperation__

#include <thread>

using namespace std;

class APOperation {
    bool _isExecuting;
    bool _isFinished;
    bool _isCancelled;
    thread *_thread;
  private:
    void execute();
  protected:
    virtual void main() = 0;
    void start();
    void startSynchronous();
    void cancel();
    void waitUntilFinish();
    virtual void didFinish();
  public:
    APOperation();
    virtual ~APOperation();
};

#endif /* defined(__APHTTPRequest__APOperation__) */
