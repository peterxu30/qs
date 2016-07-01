//
//  action.cpp
//  qs
//
//  Created by Peter Xu on 6/29/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "action.hpp"

Action * Action::addFlag(Token::Type flag) {
    this->flags.push_back(flag);
    return this;
}

Action * Action::addArg(string arg) {
    this->args.push_back(arg);
    return this;
}

