//
//  Tokenizer.cpp
//  qs
//
//  Created by Peter Xu on 6/28/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "tokenizer.hpp"

list<Token *> Tokenizer::tokenize(int rawc, const char * raw[]) {
    list<Token *> tokens;
    
    int index = 1;
    while (index < rawc) {
        string currentString = raw[index];
        string loweredCurrentString = currentString;
        std::transform(loweredCurrentString.begin(), loweredCurrentString.end(), loweredCurrentString.begin(), ::tolower);
        Token::Type type;
        
        if (loweredCurrentString == "init") {
            type = Token::INIT;
        } else if (loweredCurrentString == "new") {
            type = Token::NEW;
        } else if (loweredCurrentString == "add") {
            type = Token::ADD;
        } else if (loweredCurrentString == "clear") {
            type = Token::CLEAR;
        } else if (loweredCurrentString == "log") {
            type = Token::LOG;
        } else if (loweredCurrentString == "rm") {
            type = Token::REMOVE;
        } else if (loweredCurrentString == "status") {
            type = Token::STATUS;
        } else if (loweredCurrentString == "switch") {
            type = Token::SWITCH;
        } else if (loweredCurrentString == "users") {
            type = Token::USERS;
        } else if (loweredCurrentString == "-msg") {
            type = Token::MSG;
        } else if (loweredCurrentString == "-file") {
            type = Token::FILE;
        } else if (loweredCurrentString == "-full") {
            type = Token::FULL;
        } else if (loweredCurrentString == "-a") {
            type = Token::ACCOUNT;
        } else {
            type = Token::CUSTOM;
        }
        
        tokens.push_back(new Token(type, currentString));
        index++;
    }
    
    return tokens;
}
