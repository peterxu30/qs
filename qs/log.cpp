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
    
//    list<string> emailMessages = LogManager::getAllSentMessages();
    list<ptree> emailMessages = LogManager::getAllSentMessages();
    
    cout << "Message Log\n";
//    for (string emailMessage : emailMessages) {
//        cout << emailMessage << '\n';
//    }
    for (ptree emailMessage : emailMessages) {
        cout << "id: " << emailMessage.get_child("id").get_value<string>() << "   ";
        cout << "date sent: " << emailMessage.get_child("time").get_value<string>() << '\n';
        cout << "subject: " << emailMessage.get_child("subject").get_value<string>() << '\n';
    }
    cout << endl;
}