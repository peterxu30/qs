//
//  switch.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "switch.hpp"

//not done, need to add add new email functionality.
void Switch::execute() {
    ASSERT(this->args.size() <= 1, "fatal: unacceptable number of addresses.");
    if (this->flags.size() == 1) {
        if (this->flags.front() == Token::ACCOUNT) {
            string email;
            string password;
            string smtpAddress;
            string smtpPort;
            
            std::cout << "Email address: ";
            std::cin >> email;
            
            std::cout << "Password: ";
            std::cin >> password;
            
            std::cout << "SMTP Address: ";
            std::cin >> smtpAddress;
            
            AccountsManager::addEmailAccount(email, password, smtpAddress, true);
            std::cout << email << " added." << std::endl;
        } else {
            std::cout << "fatal: flag not acceptable." << std::endl;
        }
    } else if (this->flags.size() == 0) {
        AccountsManager::switchActiveEmailAccount(this->args.front());
    }
}