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
#include "utilities.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace Poco;
using namespace Poco::Net;

class EmailManager
{
    
public:
    static MailMessage * createEmail(vector<string> emailRecipients, string emailSubject, string emailContent);
    
    static MailMessage * createEmail(vector<string> emailRecipients, string emailSubject, string emailContent, std::unordered_map<string, string> fileAttachmentMap);
    
    static int sendEmail(MailMessage * email);
    
    static int stageFile(string filePath);
    
    static bool fileStagerIsInitialized();
    
};


#endif /* email_manager_hpp */
