//
//  email_networking_manager.hpp
//  qs
//
//  Created by Peter Xu on 4/22/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef email_networking_manager_hpp
#define email_networking_manager_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/AutoPtr.h>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

using namespace Poco::Net;
using namespace Poco;

class EmailNetworkingManager
{
    
public:
    static int sendEmail(vector<string> emailRecipients, string emailSubject, string emailContent);
    
    static int sendEmail(MailMessage * email);
    
};

#endif /* email_networking_manager_hpp */
