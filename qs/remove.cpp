//
//  remove.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "remove.hpp"

void Remove::execute() {
    
    if (this->flags.size() > 0) {
        Token::Type flag = this->flags.front();
        switch (flag) {
            case Token::ACCOUNT:
                break;
            default:
                std::cout << "fatal: flag not recognized" << std::endl;
                break;
        }
    } else {
        for (string file : this->args) {
            EmailManager::unstageFile(file);
        }
    }
    
}