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
    std::string activeEmail = AccountsManager::getActiveEmailAddress();
    
    for (std::string email : emails) {
        std::cout << email << "\n";
    }
    std::cout << endl;
}