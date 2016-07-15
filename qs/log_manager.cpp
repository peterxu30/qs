//
//  log_manager.cpp
//  qs
//
//  Created by Peter Xu on 5/19/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "log_manager.hpp"

char * LogManager::LOG_FILE_PATH = "qs_data/log.txt";
char * LogManager::LOG_DIR_PATH = "qs_data/log/";

bool LogManager::logIsInitialized() {
    return boost::filesystem::exists(LOG_FILE_PATH)
        && boost::filesystem::exists(LOG_DIR_PATH);
}

list<string> LogManager::getAllSentMessages() {
    list<string> fileContents;
    Utilities::getFileContents(LOG_FILE_PATH, fileContents);
    return fileContents;
}

void LogManager::logEmail(string sender, list<string> emailRecipients, string emailSubject, string emailContent) {
    logEmail(sender, emailRecipients, emailSubject, emailContent, std::unordered_map<string, string>());
}

void LogManager::logEmail(string sender, list<string> emailRecipients, string emailSubject, string emailContent, std::unordered_map<string, string> fileAttachmentMap) {
    boost::uuids::uuid logID = (boost::uuids::random_generator()());
    std::list<string> fileContents;
    const char * logIDstr = boost::lexical_cast<string>(logID).c_str();
    const char * logFilePath = (LOG_DIR_PATH + string(logIDstr) + ".txt").c_str();
    addEmailToLog(logIDstr);
    
    string senderLine = "Sender: " + sender + "\n";
    fileContents.push_back(senderLine);
    
    string recipientsLine = "Recipients:";
    list<string>::iterator iter = emailRecipients.begin();
    list<string>::iterator end = emailRecipients.end();
    while (iter != end) {
        recipientsLine += " " + *iter;
        iter++;
    }
    recipientsLine += "\n";
    fileContents.push_back(recipientsLine);
    
    string subjectLine = "Subject: " + emailSubject + "\n";
    fileContents.push_back(subjectLine);
    
    string contentLine = "Content: " + emailContent + "\n";
    fileContents.push_back(contentLine);
    
    string attachmentsLine = "Attachments:";
    for (auto kv : fileAttachmentMap) {
        attachmentsLine += " " + kv.second;
    }
    attachmentsLine += "\n";
    fileContents.push_back(attachmentsLine);
    
    Utilities::rebuildFile(logFilePath, fileContents);
    cout << "logged.";
}

void LogManager::addEmailToLog(string fileName) { //maybe add more details later
    std::list<string> fileContents;
    Utilities::getFileContents(LOG_FILE_PATH, fileContents);
    fileContents.push_front(fileName);
    Utilities::rebuildFile(LOG_FILE_PATH, fileContents);
}