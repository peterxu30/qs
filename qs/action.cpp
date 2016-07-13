//
//  action.cpp
//  qs
//
//  Created by Peter Xu on 6/29/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "action.hpp"

Action * Action::addFlag(Token::Type flag) {
    this->flags.push_back(flag);
    return this;
}

Action * Action::addArg(std::string arg) {
    this->args.push_back(arg);
    return this;
}

Token::Type Action::frontFlag() {
    if (this->flags.size() > 0) {
        return this->flags.front();
    } else {
        throw std::out_of_range("no flags");
    }
}

void Action::popFrontFlag() {
    if (this->flags.size() > 0) {
        this->flags.pop_front();
    } else {
        throw std::out_of_range("no flags");
    }
}

string Action::frontArg() {
    if (this->args.size() > 0) {
        return this->args.front();
    } else {
        throw std::out_of_range("no args");
    }
}

void Action::popFrontArg() {
    if (this->args.size() > 0) {
        this->args.pop_front();
    } else {
        throw std::out_of_range("no args");
    }
}
