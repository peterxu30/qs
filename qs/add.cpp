//
//  add.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "add.hpp"

void Add::execute() {
    for (string fileName : this->args) {
        EmailManager::stageFile(fileName);
    }
}