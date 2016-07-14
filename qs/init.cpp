//
//  init.cpp
//  qs
//
//  Created by Peter Xu on 6/29/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "init.hpp"

void Init::execute() {
    if (!this->flags.empty()) {
        throw std::length_error("new can have zero flags");
    }
    QSManager::initializeQuickSend();
}