//
//  clear.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "clear.hpp"

void Clear::execute() {
    EmailManager::removeAllStagedFiles();
}