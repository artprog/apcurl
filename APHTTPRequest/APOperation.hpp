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
#include <mutex>

using namespace std;

class APOperation {
    struct State {
      bool isExecuting : 1;
      bool isFinished  : 1;
      bool isCancelled : 1;
      State() : isExecuting(0), isFinished(0), isCancelled(0) { }
    };
    State _state;
    thread *_thread;
    recursive_mutex _mutex;
  private:
    void execute();
    void setExecuting(bool executing);
    void setFinished(bool finished);
    void setCancelled(bool cancelled);
  protected:
    virtual void mainAsynchronous() = 0;
    virtual void mainSynchronous() = 0;
    void start();
    void startSynchronous();
    void cancel();
    void waitUntilFinish();
    virtual void willStart();
    virtual void didFinish();
  public:
    APOperation();
    virtual ~APOperation();
    bool isExecuting();
    bool isFinished();
    bool isCancelled();
};

#endif /* defined(__APHTTPRequest__APOperation__) */
