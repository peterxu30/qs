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
char * LogManager::LOG_FILES_KEY = "files";

bool LogManager::logIsInitialized() {
    return boost::filesystem::exists(LOG_FILE_PATH)
        && boost::filesystem::exists(LOG_DIR_PATH);
}

list<string> LogManager::getAllSentMessages() {
    ptree log;
    Utilities::convertJsonToPtree(LOG_FILE_PATH, log);
    list<string> logList = Utilities::asList(log, LOG_FILES_KEY);
    return logList;
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
    
    log.put("subject", emailSubject);
    
    log.put("content", emailContent);
    
    for (auto kv : fileAttachmentMap) {
        ptree atree;
        atree.put("", kv.second);
        attachments.push_back(std::make_pair("", atree));
    }
    log.add_child("attachments", attachments);
    Utilities::rebuildFile(logFilePath, log);
}

void LogManager::addEmailToLog(string fileName) { //maybe add more details later
    ptree fileContents;
    Utilities::convertJsonToPtree(LOG_FILE_PATH, fileContents);
    ptree temp;
    temp.put("", fileName);
    fileContents.get_child(LOG_FILES_KEY).push_back(std::make_pair("", temp));
    Utilities::rebuildFile(LOG_FILE_PATH, fileContents);
}
