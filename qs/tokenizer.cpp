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
        std::transform(currentString.begin(), currentString.end(), currentString.begin(), ::tolower);
        Token::Type type;
        
        if (currentString == "init") {
            type = Token::INIT;
        } else if (currentString == "new") {
            type = Token::NEW;
        } else if (currentString == "add") {
            type = Token::ADD;
        } else if (currentString == "clear") {
            type = Token::CLEAR;
        } else if (currentString == "log") {
            type = Token::LOG;
        } else if (currentString == "switch") {
            type = Token::SWITCH;
        } else if (currentString == "rm") {
            type = Token::REMOVE;
        } else if (currentString == "-msg") {
            type = Token::MSG;
        } else if (currentString == "-file") {
            type = Token::FILE;
        } else if (currentString == "-full") {
            type = Token::FULL;
        } else if (currentString == "-a") {
            type = Token::ACCOUNT;
        } else {
            type = Token::CUSTOM;
        }
        
        tokens.push_back(new Token(type, currentString));
        index++;
    }
    
    return tokens;
}
