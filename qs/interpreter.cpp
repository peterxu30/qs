//
//  interpreter.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "interpreter.hpp"

void Interpreter::eval(list<Token *> tokens) {
    Token * token = tokens.front();
    tokens.pop_front();

    
    Action * action;
    
    if (token->type == Token::INIT) {
        action = new Init();
    } else if (token->type == Token::NEW) {
        action = new New();
    } else if (token->type == Token::ADD) {
        action = new Add();
    } else if (token->type == Token::CLEAR) {
        action = new Clear();
    } else if (token->type == Token::LOG) {
        action = new Log();
    } else if (token->type == Token::SWITCH) {
        action = new Switch();
    } else if (token->type == Token::REMOVE) {
        action = new Remove();
    } else {
        std::cerr << "fatal: " << token->tokenString << " is not a recognized command.";
        std::terminate();
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
}
