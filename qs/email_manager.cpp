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
//char * EmailManager::LOG_FILE_PATH = "qs_data/log.txt";

MailMessage * EmailManager::createEmail(list<string>& emailRecipients, string emailSubject, string emailContent)
{
    MailMessage * newEmail = new MailMessage();
    
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

MailMessage * EmailManager::createEmail(list<string>& emailRecipients, string emailSubject, string emailContent, std::unordered_map<string, string>& fileAttachmentMap)
{
    MailMessage * newEmail = createEmail(emailRecipients, emailSubject, emailContent);
    
//    string currentWorkingDirectory = getcwd(NULL, 0);
    
    cout << fileAttachmentMap.size() << endl;
    
    if (!fileAttachmentMap.empty()) {
        for (auto kv : fileAttachmentMap) {
            string fileAttachmentName = kv.first;
            string fileAttachmentPath = kv.second;
            
            std::stringstream absoluteFileAttachmentPathStream;
            
            newEmail->addAttachment(fileAttachmentName, new FilePartSource(fileAttachmentPath));
        }
    }
    
    return newEmail;
}

MailMessage * EmailManager::createEmailFromStaging(list<string>& emailRecipients, string emailSubject, string emailContent) {
    unordered_map<string, string> fileAttachmentMap;
    popAllStagedFiles(fileAttachmentMap);
    return createEmail(emailRecipients, emailSubject, emailContent, fileAttachmentMap);
}

void EmailManager::sendEmail(MailMessage * email)
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
            session.close();
            uninitializeSSL();
            throw e;
        }
    } catch (NetException &e) {
        throw e;
    }
}

int EmailManager::stageFile(string filePath) {
    ASSERT(fileStagerIsInitialized(), "fatal: file stager not found.");

    if (filePath == "") {
        return 0;
    }
    
    if (!boost::filesystem::exists(filePath)) {
        throw std::invalid_argument(filePath + " not found");
    }
    
    if (!fileIsStaged(filePath)) {
        string fileName = getFileName(filePath);
        string absoluteFilePath = getAbsoluteFilePath(filePath);
        
        list<string> fileContents;
        Utilities::getFileContents(STAGE_FILE_PATH, fileContents);
        string fileLine = fileName + " " + absoluteFilePath;
        fileContents.push_back(fileLine);
        
        return Utilities::rebuildFile(STAGE_FILE_PATH, fileContents);
    }
    return 0;
}

int EmailManager::stageFiles(list<string> filePaths) {
    for (string filePath : filePaths) {
        stageFile(filePath);
    }
    return 0;
}

int EmailManager::unstageFile(string filePath) {
    ASSERT(fileStagerIsInitialized(), "fatal: file stager not found.");
    string absoluteFilePath = getAbsoluteFilePath(filePath);
    
    string fileLine = getFileName(filePath) + " " + absoluteFilePath;
    
    list<string> fileContents;
    Utilities::getFileContents(STAGE_FILE_PATH, fileContents);
    fileContents.remove(fileLine);
    return Utilities::rebuildFile(STAGE_FILE_PATH, fileContents);
}

void EmailManager::getAllStagedFiles(unordered_map<string, string>& fileContents) {
    list<string> fileList;
    Utilities::getFileContents(STAGE_FILE_PATH, fileList);
    
    for (string fileLine : fileList) {
        vector<string> tokens;
        boost::algorithm::split(tokens, fileLine, boost::algorithm::is_any_of(" "));
        ASSERT(tokens.size() == 2, "fatal: staging file failed.");
        fileContents[tokens[0]] = tokens[1];
    }
}

int EmailManager::popAllStagedFiles(unordered_map<string, string>& fileContents) {
    getAllStagedFiles(fileContents);
    return removeAllStagedFiles();
}

int EmailManager::removeAllStagedFiles() {
    list<string> empty;
    Utilities::rebuildFile(STAGE_FILE_PATH, empty);
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

bool EmailManager::fileIsStaged(string filePath) {
    boost::filesystem::path inputPath(filePath);
    list<string> fileContents;
    Utilities::getFileContents(STAGE_FILE_PATH, fileContents);

    for (string fileLine : fileContents) {
        vector<string> tokens;
        boost::algorithm::split(tokens, fileLine, boost::algorithm::is_any_of(" "));
        boost::filesystem::path stagedFilePath(tokens[1]);
        if (boost::filesystem::equivalent(inputPath, stagedFilePath)) {
            return true;
        }
    }
    return false;
}

string EmailManager::getAbsoluteFilePath(string localPath) {
    return boost::filesystem::canonical(localPath, boost::filesystem::current_path()).template string<string>();
}
