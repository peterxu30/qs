//
//  Token.hpp
//  qs
//
//  Created by Peter Xu on 6/28/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef token_hpp
#define token_hpp

#include <stdio.h>
#include <string>

using std::string;

struct Token {
public:
    enum Type {
        INIT,
        NEW,
        ADD,
        CLEAR,
        LOG,
        REMOVE,
        STATUS,
        SWITCH,
        USERS,
        MSG,
        FILE,
        FULL,
        ACCOUNT,
        CUSTOM //user input (e.g. file names)
    };
    
    string tokenString;
    Type type;
    
    Token(Type type, string tokenString);
    
    bool isCommand();
    bool isFlag();

private:
    const int numberOfCommands = 8;
    const int numberOfFlags = 4;
};

#endif /* token_hpp */
