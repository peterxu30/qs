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
    
    std::fstream fileStagerStream("qs_data/stage.txt");
    list<string> fileContents;
    string stageFileLine;
    if (fileStagerStream.is_open()) {
        while (getline(fileStagerStream, stageFileLine, '\n')) {
            fileContents.push_back(stageFileLine);
        }
    }
    fileContents.push_back(filePath);

    return Utilities::rebuildFile("qs_data/stage.txt", fileContents);
}

bool EmailManager::fileStagerIsInitialized() {
    return boost::filesystem::exists("qs_data/stage.txt");
}
