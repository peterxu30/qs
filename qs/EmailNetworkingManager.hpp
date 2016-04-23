//
//  EmailNetworkingManager.hpp
//  qs
//
//  Created by Peter Xu on 4/22/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef EmailNetworkingManager_hpp
#define EmailNetworkingManager_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/AutoPtr.h>

using namespace std;
using namespace Poco::Net;
using namespace Poco;

class EmailNetworkingManager
{
    
public:
    int sendEmail(vector<string> emailRecipients, string emailSubject, string emailContent);
    
};

#endif /* EmailNetworkingManager_hpp */
