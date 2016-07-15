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
    
    std::cout << "To: ";
    getline(cin, recipients);
    cin.clear();

    std::cout << "Title: ";
    getline(cin, subject);
    cin.clear();
    
    Token::Type flag;
    if (!this->flags.empty()) {
        flag = flags.front();
    } else {
        flag = Token::FULL;
    }
    
    list<string> recipientList;
    boost::algorithm::split(recipientList, recipients, boost::algorithm::is_any_of(" "));
    list<string> attachmentList;
    
    MailMessage * email;
    unordered_map<string, string> fileAttachmentMap;

    if (flag == Token::FULL) {
        body = promptMsg();
        attachmentList = promptFile();
        EmailManager::getAllStagedFiles(fileAttachmentMap);
        EmailManager::stageFiles(attachmentList);
        email = EmailManager::createEmailFromStaging(recipientList, subject, body);
    } else if (flag == Token::MSG) {
        body = promptMsg();
        email = EmailManager::createEmail(recipientList, subject, body);
    } else if (flag == Token::FILE) {
        attachmentList = promptFile();
        EmailManager::getAllStagedFiles(fileAttachmentMap);
        EmailManager::stageFiles(attachmentList);
        email = EmailManager::createEmailFromStaging(recipientList, subject, body);
    } else {
        throw std::invalid_argument("unrecognized flag");
    }
    
    std::cout << "sending email...\n";
    try {
        EmailManager::sendEmail(email);
        LogManager::logEmail(AccountsManager::getActiveEmailAddress(), recipientList, subject, body, fileAttachmentMap);
    } catch (std::exception& e) {
        throw std::runtime_error("email failed to send");
    }
    delete email;
}//issue exists with -msg logging

string New::promptMsg() {
    string body;
    std::cout << "Body: ";
    getline(cin, body);
    cin.clear();
    return body;
}

list<string> New::promptFile() {
    string attachments;
    std::cout << "Attachments: ";
    getline(cin, attachments);
    cin.clear();
    list<string> attachmentList;
    boost::algorithm::split(attachmentList, attachments, boost::algorithm::is_any_of(" "));
    return attachmentList;
}
