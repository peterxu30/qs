//
//  remove.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "remove.hpp"

void Remove::execute() {
    
    if (this->flags.empty()) {
        for (string file : this->args) {
            EmailManager::unstageFile(file);
        }
    } else {
        Token::Type flag = this->frontFlag();
        if (flag == Token::ACCOUNT) {
            AccountsManager::removeEmailAccount(this->frontArg());
        } else {
            throw std::invalid_argument("flag not recognized");
        }
    }
}
