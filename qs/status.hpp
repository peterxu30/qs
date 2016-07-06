//
//  status.hpp
//  qs
//
//  Created by Peter Xu on 7/5/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef status_hpp
#define status_hpp

#include <stdio.h>
#include "action.hpp"
#include "email_manager.hpp"
#include <unordered_map>

class Status : public Action {
public:
    void execute() override;
};

#endif /* status_hpp */
