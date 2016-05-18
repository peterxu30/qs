//
//  email_message_creator.hpp
//  qs
//
//  Created by Peter Xu on 4/23/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef email_message_creator_hpp
#define email_message_creator_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/FilePartSource.h>

using std::string;
using std::vector;
using namespace Poco::Net;

class EmailMessageCreator
{
    
public:
    static MailMessage * createEmail(vector<string> emailRecipients, string emailSubject, string emailContent);
    
    static MailMessage * createEmail(vector<string> emailRecipients, string emailSubject, string emailContent, std::unordered_map<string, string> fileAttachmentMap);
};

#endif /* email_message_creator_hpp */
