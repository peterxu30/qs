//
//  log_manager.cpp
//  qs
//
//  Created by Peter Xu on 5/19/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "log_manager.hpp"

bool LogManager::logIsInitialized() {
    return boost::filesystem::exists("qs_data/log.txt");
}