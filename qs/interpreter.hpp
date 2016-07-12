//
//  interpreter.hpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef interpreter_hpp
#define interpreter_hpp

#include <stdio.h>
#include <iostream>
#include <list>

#include "action.hpp"
#include "add.hpp"
#include "clear.hpp"
#include "error_checking_macros.h"
#include "init.hpp"
#include "log.hpp"
#include "new.hpp"
#include "remove.hpp"
#include "status.hpp"
#include "switch.hpp"
#include "token.hpp"
#include "users.hpp"

using std::list;

namespace Interpreter {
    
    void eval(list<Token *> tokens);
    
}

#endif /* interpreter_hpp */
