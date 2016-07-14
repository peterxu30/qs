//
//  clear.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "clear.hpp"

void Clear::execute() {
    if (!this->flags.empty()) {
        throw std::length_error("log can have zero flags");
    }
    
    if (!this->args.empty()) {
        throw std::length_error("log can have zero arguments");
    }
    
    EmailManager::removeAllStagedFiles();
}