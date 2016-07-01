//
//  action.hpp
//  qs
//
//  Created by Peter Xu on 6/29/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef action_hpp
#define action_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <string>

#include "error_checking_macros.h"
#include "token.hpp"

using std::list;
using std::string;

class Action {
public:
    Action * addFlag(Token::Type flag);
    Action * addArg(string arg);
    virtual void execute() = 0;

protected:
    list<Token::Type> flags;
    list<string> args;
};

#endif /* action_hpp */
