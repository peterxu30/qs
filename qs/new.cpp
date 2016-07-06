//
//  new.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "new.hpp"

void New::execute() {
    ASSERT(this->flags.size() <= 1, "fatal: new can have zero or one flags");
    
    if (!this->flags.empty()) {
        Token::Type flag = flags.front();
        
        switch (flag) {
            case Token::MSG:
                break;
            case Token::FILE:
                break;
            case Token::FULL:
                break;
            default:
                std::cout << "fatal: unrecognized argument: " << flag << std::endl;
                break;
        }
    } else {
        
    }
}