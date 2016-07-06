//
//  switch.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "switch.hpp"

void Switch::execute() {
    ASSERT(this->args.size() == 1, "fatal: Unacceptable number of arguments given.");
    AccountsManager::switchActiveEmailAccount(this->args.front());
}