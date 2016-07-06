//
//  log.hpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef log_hpp
#define log_hpp

#include <stdio.h>

#include "action.hpp"
#include "user_interface.hpp"

class Log : public Action {
public:
    void execute() override;
};

#endif /* log_hpp */
