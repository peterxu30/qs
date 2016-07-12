//
//  users.hpp
//  qs
//
//  Created by Peter Xu on 7/11/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef users_hpp
#define users_hpp

#include <stdio.h>
#include <list>
#include <string>
#include <unordered_map>

#include "action.hpp"
#include "accounts_manager.hpp"

class Users : public Action {
public:
    void execute();
};
#endif /* user_hpp */
