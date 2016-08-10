//
//  users.cpp
//  qs
//
//  Created by Peter Xu on 7/11/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "users.hpp"

void Users::execute() {
    if (!this->flags.empty()) {
        throw std::length_error("log can have zero flags");
    }
    
    if (!this->args.empty()) {
        throw std::length_error("log can have zero arguments");
    }
    
    std::list<std::string> emails = AccountsManager::getAllEmailsAsStrings();
    std::string activeEmailAccount;
    try {
        activeEmailAccount = AccountsManager::getActiveEmailAddress();
    } catch (std::exception& e) {
        activeEmailAccount = "";
    }
    std::cout << "\n";
    for (std::string email : emails) {
        if (email == activeEmailAccount) {
            std::cout << "* ";
        }
        std::cout << email << "\n";
    }
    std::cout << endl;
}
