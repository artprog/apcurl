//
//  HTTPRequestTypes.hpp
//  APHTTPRequest
//
//  Created by Adam Zugaj on 12/07/16.
//  Copyright © 2016 ArtProg. All rights reserved.
//

#ifndef HTTPRequestTypes_hpp
#define HTTPRequestTypes_hpp

#include <stdio.h>

namespace AP {
namespace HTTPRequest {

    typedef enum {
        HTTPMethodGET = 0,
        HTTPMethodPOST
    } HTTPMethod;

}
}

#endif /* HTTPRequestTypes_hpp */
