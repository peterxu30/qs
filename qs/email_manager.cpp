//
//  email_manager.cpp
//  qs
//
//  Created by Peter Xu on 6/5/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//
//  Credit:
//  The majority of the sendEmail method was borrowed from http://axistasoft.com/blog/poco/poco-net/item/sending-email-messages-using-poco-smtpclientsession-class and tailored to suit my purposes.
//

#include "email_manager.hpp"

char * EmailManager::STAGE_FILE_PATH = "qs_data/stage.txt";

MailMessage * EmailManager::createEmail(vector<string> emailRecipients, string emailSubject, string emailContent)
{
    MailMessage * newEmail = new MailMessage();
    
    //    newEmail->setSender("atdpjava15@gmail.com"); //temporary sender
    newEmail->setSender(AccountsManager::getActiveEmailAddress());
    
    for (const string recipient : emailRecipients) {
        newEmail->addRecipient(MailRecipient(MailRecipient::PRIMARY_RECIPIENT, recipient));
    }
    
    emailSubject = MailMessage::encodeWord(emailSubject, "UTF-8");
    
    newEmail->setSubject(emailSubject);
    newEmail->setContentType("text/plain; charset=UTF-8");
    newEmail->setContent(emailContent, MailMessage::ENCODING_8BIT);
    
    return newEmail;
}

//NEED TO FIX
//STAGING FILES ALREADY STORES THE ABSOLUTE FILE PATHS. THE FILE NAMES SHOULD JUST BE THE FILE NAMES. NOT CUSTOM. PERHAPS CHANGE THE WAY FILES ARE TRACKED ON STAGE.TXT.
// LOCALFILEPATH ABSOLUTEFILEPATH
MailMessage * EmailManager::createEmail(vector<string> emailRecipients, string emailSubject, string emailContent, std::unordered_map<string, string> fileAttachmentMap)
{
    MailMessage * newEmail = createEmail(emailRecipients, emailSubject, emailContent);
    
    string currentWorkingDirectory = getcwd(NULL, 0);
    
    for (std::unordered_map<string, string>::iterator i = fileAttachmentMap.begin(); i != fileAttachmentMap.end(); i++) {
        string fileAttachmentName = i->first;
        string relativeFileAttachmentPath = i->second;
        
        std::stringstream absoluteFileAttachmentPathStream;
        absoluteFileAttachmentPathStream << currentWorkingDirectory << "/" << relativeFileAttachmentPath;
        string absoluteFileAttachmentPath = absoluteFileAttachmentPathStream.str();
        
        newEmail->addAttachment(fileAttachmentName, new FilePartSource(absoluteFileAttachmentPath));
    }
    
    return newEmail;
}

MailMessage * EmailManager::createEmailFromStaging(vector<string> emailRecipients, string emailSubject, string emailContent) {
    unordered_map<string, string> fileAttachmentMap;
    popAllStagedFiles(fileAttachmentMap);
    return createEmail(emailRecipients, emailSubject, emailContent, fileAttachmentMap);
}

int EmailManager::sendEmail(MailMessage * email)
{
    AccountsManager::Account activeAccount = AccountsManager::getActiveEmailAccount();
    string host = activeAccount.smtpAddress;
    UInt16 port = 465;
    string user = activeAccount.email;
    string password = activeAccount.password;
    
    try {
        initializeSSL();
        SharedPtr<InvalidCertificateHandler> ptrHandler = new AcceptCertificateHandler(false);
        Context::Ptr ptrContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
        SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);
        
        SocketAddress sa(host, port);
        SecureStreamSocket socket(sa);
        SMTPClientSession session(socket);
        
        try {
            session.login(SMTPClientSession::AUTH_LOGIN, user, password);
            session.sendMessage(*email);
            cout << "Message successfully sent." << endl;
            session.close();
            uninitializeSSL();
        } catch (SMTPException &e) {
            cerr << e.displayText() << endl;
            session.close();
            uninitializeSSL();
            return 0;
        }
    } catch (NetException &e) {
        cerr << e.displayText() << endl;
        return 0;
    }
    return 0;
}

int EmailManager::stageFile(string filePath) {
    ASSERT(fileStagerIsInitialized(), "Staging failed: File stager not found.");
    
    vector<string> tokens;
    boost::algorithm::split(tokens, filePath, boost::algorithm::is_any_of("/"));
    string fileName = tokens[tokens.size() - 1];

    string absoluteFilePath = getAbsoluteFilePath(filePath);
    
    list<string> fileContents;
    Utilities::getFileContents(STAGE_FILE_PATH, fileContents);
    fileContents.push_back(fileName + " " + absoluteFilePath);

    return Utilities::rebuildFile(STAGE_FILE_PATH, fileContents);
}

int EmailManager::unstageFile(string filePath) {
    ASSERT(fileStagerIsInitialized(), "Staging failed: File stager not found.");
    
    string fileLine = getFileName(filePath) + " " + getAbsoluteFilePath(filePath);
    
    list<string> fileContents;
    Utilities::getFileContents(STAGE_FILE_PATH, fileContents);
    fileContents.remove(fileLine);
    return Utilities::rebuildFile(STAGE_FILE_PATH, fileContents);
}

void EmailManager::getAllStagedFiles(unordered_map<string, string> fileContents) {
    list<string> fileList;
    Utilities::getFileContents(STAGE_FILE_PATH, fileList);
    
    list<string>::iterator iter = fileList.begin();
    list<string>::iterator endIter = fileList.end();
    
    while (iter != endIter) {
        string fileLine = *iter;
        vector<string> tokens;
        boost::algorithm::split(tokens, fileLine, boost::algorithm::is_any_of(" "));
        ASSERT(tokens.size() == 2, "Staging File Error: Something dun goofed.");
        fileContents[tokens[0]] = tokens[1];
        iter++;
    }
}

int EmailManager::popAllStagedFiles(unordered_map<string, string> fileContents) {
    getAllStagedFiles(fileContents);
    return removeAllStagedFiles();
}

int EmailManager::removeAllStagedFiles() {
    fopen(STAGE_FILE_PATH, "w");
    if (fileStagerIsInitialized()) {
        return 0;
    }
    return 1;
}

bool EmailManager::fileStagerIsInitialized() {
    return boost::filesystem::exists(STAGE_FILE_PATH);
}

string EmailManager::getFileName(string filePath) {
    vector<string> tokens;
    boost::algorithm::split(tokens, filePath, boost::algorithm::is_any_of("/"));
    return tokens[tokens.size() - 1];
}

string EmailManager::getAbsoluteFilePath(string localPath) {
    return (string) getcwd(NULL, 0) + "/" + localPath;
}
