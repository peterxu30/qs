//
//  log.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "log.hpp"

void Log::execute() {
    if (!this->flags.empty()) {
        throw std::length_error("log can have zero flags");
    }
    
    if (!this->args.empty()) {
        throw std::length_error("log can have zero arguments");
    }
    
    list<string> emailMessages = LogManager::getAllSentMessages();
    
    cout << "Message Log\n";
    for (string emailMessage : emailMessages) {
        cout << emailMessage << '\n';
    }
    cout << endl;
}