//
//  interpreter.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "interpreter.hpp"

void Interpreter::eval(list<Token *> tokens) {
    if (tokens.size() == 0) {
        return;
    }
    Token * token = tokens.front();
    tokens.pop_front();

    
    Action * action = nullptr;
    Token::Type type = token->type;
    
    switch (type) {
        case Token::INIT:
            action = new Init();
            break;
        case Token::NEW:
            action = new New();
            break;
        case Token::ADD:
            action = new Add();
            break;
        case Token::CLEAR:
            action = new Clear();
            break;
        case Token::LOG:
            action = new Log();
            break;
        case Token::REMOVE:
            action = new Remove();
            break;
        case Token::STATUS:
            action = new Status();
            break;
        case Token::SWITCH:
            action = new Switch();
            break;
        case Token::USERS:
            action = new Users();
            break;
        default:
            std::cerr << "fatal: " << token->tokenString << " is not a recognized command." << std::endl;
            break;
    }
    
    delete token;
    
    while (!tokens.empty()) {
        token = tokens.front();
        tokens.pop_front();
        
        if (token->isFlag()) {
            action->addFlag(token->type);
        } else {
            action->addArg(token->tokenString);
        }
        delete token;
    }
    
    action->execute();
    delete action; //fix
}
