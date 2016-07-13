//
//  log.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "log.hpp"

void Log::execute() {
    if (this->flags.size() > 0) {
        throw std::length_error("log can have zero flags");
    }
    
    if (this->args.size() > 0) {
        throw std::length_error("log can have zero arguments");
    }
    
    UserInterface::displayAllEmailMessages();
}