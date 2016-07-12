//
//  email_manager.hpp
//  qs
//
//  Created by Peter Xu on 6/5/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef email_manager_hpp
#define email_manager_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/AutoPtr.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/SSLManager.h>

#include "accounts_manager.hpp"
#include "error_checking_macros.h"
#include "utilities.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;
using namespace Poco;
using namespace Poco::Net;

class EmailManager
{
    
public:
    static MailMessage * createEmail(vector<string> emailRecipients, string emailSubject, string emailContent);
    static MailMessage * createEmail(vector<string> emailRecipients, string emailSubject, string emailContent, std::unordered_map<string, string> fileAttachmentMap);
    static MailMessage * createEmailFromStaging(vector<string> emailRecipients, string emailSubject, string emailContent);
    static int sendEmail(MailMessage * email);
    static list<string> getAllSentMessages();
    static int stageFile(string filePath);
    static int unstageFile(string filePath);
    static void getAllStagedFiles(unordered_map<string, string>& fileContents);
    static int popAllStagedFiles(unordered_map<string, string>& fileContents);
    static int removeAllStagedFiles();
    static bool fileIsStaged(string filePath);
    static string getAbsoluteFilePath(string localPath);
    static bool fileStagerIsInitialized();
    
private:
    static char * STAGE_FILE_PATH;
    static char * LOG_FILE_PATH;
    static void logEmail(string sender, vector<string> emailRecipients, string emailSubject, string emailContent);
    static void logEmail(string sender, vector<string> emailRecipients, string emailSubject, string emailContent, std::unordered_map<string, string> fileAttachmentMap);
    static void addEmailToLog(string fileName);
    static string getFileName(string filePath);
    
};


#endif /* email_manager_hpp */
