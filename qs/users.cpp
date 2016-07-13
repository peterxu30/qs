//
//  users.cpp
//  qs
//
//  Created by Peter Xu on 7/11/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "users.hpp"

void Users::execute() {
    std::list<std::string> emails = AccountsManager::getAllEmailsAsStrings();
    std::string activeEmailAccount = AccountsManager::getActiveEmailAddress();
    std::cout << "\n";
    for (std::string email : emails) {
        if (email == activeEmailAccount) {
            std::cout << "* ";
        }
        std::cout << email << "\n";
    }
    std::cout << endl;
}