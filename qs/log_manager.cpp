//
//  log_manager.cpp
//  qs
//
//  Created by Peter Xu on 5/19/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "log_manager.hpp"

char * LogManager::LOG_FILE_PATH = "qs_data/log.txt";

bool LogManager::logIsInitialized() {
    return boost::filesystem::exists("qs_data/log.txt");
}

list<string> LogManager::getAllSentMessages() {
    list<string> fileContents;
    Utilities::getFileContents(LOG_FILE_PATH, fileContents);
    return fileContents;
}

void LogManager::logEmail(string sender, vector<string> emailRecipients, string emailSubject, string emailContent) {
    logEmail(sender, emailRecipients, emailSubject, emailContent, std::unordered_map<string, string>());
}

void LogManager::logEmail(string sender, vector<string> emailRecipients, string emailSubject, string emailContent, std::unordered_map<string, string> fileAttachmentMap) {
    boost::uuids::uuid logID = (boost::uuids::random_generator()());
    std::list<string> fileContents;
    const char * logFilePath = (boost::lexical_cast<string>(logID) + ".txt").c_str();
    addEmailToLog(logFilePath);
    
    string senderLine = "Sender: " + sender + "\n";
    fileContents.push_back(senderLine);
    
    string recipientsLine = "Recipients:";
    vector<string>::iterator iter = emailRecipients.begin();
    vector<string>::iterator end = emailRecipients.end();
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
}

void LogManager::addEmailToLog(string fileName) { //maybe add more details later
    std::list<string> fileContents;
    Utilities::getFileContents(LOG_FILE_PATH, fileContents);
    fileContents.push_front(fileName);
    Utilities::rebuildFile(LOG_FILE_PATH, fileContents);
}