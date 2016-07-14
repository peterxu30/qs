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
    if (this->flags.size() > 1) {
        throw std::length_error("unacceptable number of flags");
    }
    
    if (this->args.size() > 1) {
        throw std::length_error("unacceptable number of addresses");
    }
    
    if (this->flags.empty()) {
        AccountsManager::switchActiveEmailAccount(this->frontArg());
    } else if (this->flags.front() == Token::ACCOUNT) {
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
            throw std::invalid_argument("flag not acceptable");
    }
}
