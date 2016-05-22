//
//  log_manager.hpp
//  qs
//
//  Created by Peter Xu on 5/19/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef log_manager_hpp
#define log_manager_hpp

#include <stdio.h>

#include <boost/filesystem.hpp>

class LogManager {
public:
    static bool logIsInitialized();
};

#endif /* log_manager_hpp */
