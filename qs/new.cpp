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
    
    string recipients;
    string title;
    string body = "";
    string attachments = "";
    
    std::cout << "To: ";
    std::cin >> recipients;
    
    std::cout << "Title: ";
    std::cin >> title;
    
    Token::Type flag;
    if (!this->flags.empty()) {
        flag = flags.front();
    } else {
        flag = Token::FULL;
    }
    
    switch (flag) {
        case Token::MSG:
            std::cout << "Body: ";
            std::cin >> body;
            break;
        case Token::FILE:
            std::cout << "Attachments: ";
            std::cin >> attachments;
            break;
        case Token::FULL:
            std::cout << "Body: ";
            std::cin >> body;
            std::cout << "Attachments: ";
            std::cin >> attachments;
            break;
        default:
            std::cout << "fatal: unrecognized argument: " << flag << std::endl;
            std::terminate();
            break;
    }
    list<string> recipientList;
    boost::algorithm::split(recipientList, recipients, boost::algorithm::is_any_of(" "));
    
    list<string> attachmentList;
    boost::algorithm::split(attachmentList, attachments, boost::algorithm::is_any_of(" "));

}

void New::interactiveNewMsg() {
    
}

void New::interactiveNewFile() {
    
}

void New::interactiveNewFull() {
    
}