//
//  log.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "log.hpp"

void Log::execute() {
    ASSERT(this->flags.size() == 0, "fatal: log can have zero flags");
    UserInterface::displayAllEmailMessages();
}