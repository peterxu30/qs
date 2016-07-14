//
//  new.cpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "new.hpp"

void New::execute() {
    if (this->flags.size() > 1) {
        throw std::length_error("new can have zero or one flags");
    }
    
    string recipients;
    string subject;
    string body = "";
    string attachments = "";
    
    std::cout << "To: ";
    std::cin >> recipients;
    
    std::cout << "Title: ";
    std::cin >> subject;
    
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
            throw std::invalid_argument("unrecognized flag");
            break;
    }
    list<string> recipientList;
    boost::algorithm::split(recipientList, recipients, boost::algorithm::is_any_of(" "));
    
    list<string> attachmentList;
    boost::algorithm::split(attachmentList, attachments, boost::algorithm::is_any_of(" "));
    
    EmailManager::stageFiles(attachmentList);
    MailMessage * email = EmailManager::createEmailFromStaging(recipientList, subject, body);
    try {
        EmailManager::sendEmail(email);
    } catch (std::exception& e) {
        throw std::runtime_error("email failed to send");
    }
}

void New::interactiveNewMsg() {
    
}

void New::interactiveNewFile() {
    
}

void New::interactiveNewFull() {
    
}