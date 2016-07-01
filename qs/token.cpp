//
//  Token.cpp
//  qs
//
//  Created by Peter Xu on 6/28/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "token.hpp"

Token::Token(Type type, string tokenString) {
    this->type = type;
    this->tokenString = tokenString;
};

bool Token::isCommand() {
    return this->type < this->numberOfCommands;
}

bool Token::isFlag() {
    return this->type >= this->numberOfCommands
        && this->type < (this->numberOfCommands + this->numberOfFlags);
}