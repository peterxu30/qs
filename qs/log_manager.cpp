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
    string logIDStr = boost::uuids::to_string(logID);
    string logFilePath(LOG_DIR_PATH);
    logFilePath.append(logIDStr);
    logFilePath.append(".txt");
    addEmailToLog(logIDStr);
    
    ptree log;
    ptree recipients;
    ptree attachments;
    log.put("sender", sender);
    
    for (string recipient : emailRecipients) {
        ptree rtree;
        rtree.put("", recipient);
        recipients.push_back(std::make_pair("", rtree));
    }
    log.add_child("recipients", recipients);
//    ptree temp; works
//    temp.put("", "test");
//    log.get_child("recipients").push_back(std::make_pair("", temp));
    
    log.put("subject", emailSubject);
    
    log.put("content", emailContent);
    
    for (auto kv : fileAttachmentMap) {
        ptree atree;
        atree.put("", kv.second);
        attachments.push_back(std::make_pair("", atree));
    }
    log.add_child("attachments", attachments);
    
    std::ostringstream buf;
    write_json(buf, log, false);
    std::string json = buf.str();
    Utilities::rebuildFile(logFilePath, json);
}

void LogManager::addEmailToLog(string fileName) { //maybe add more details later
    std::list<string> fileContents;
    Utilities::getFileContents(LOG_FILE_PATH, fileContents);
    fileContents.push_front(fileName);
    Utilities::rebuildFile(LOG_FILE_PATH, fileContents);
}
