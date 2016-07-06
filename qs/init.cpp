//
//  init.cpp
//  qs
//
//  Created by Peter Xu on 6/29/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "init.hpp"

void Init::execute() {
    ASSERT(this->flags.size() == 0, "fatal: new can have zero flags");
    QSManager::initializeQuickSend();
}