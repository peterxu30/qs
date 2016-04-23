//
//  EmailMessageCreator.cpp
//  qs
//
//  Created by Peter Xu on 4/23/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "EmailMessageCreator.hpp"

MailMessage * EmailMessageCreator::createEmail(vector<string> emailRecipients, string emailSubject, string emailContent)
{
    MailMessage * newEmail = new MailMessage();
    
    newEmail->setSender("atdpjava15@gmail.com"); //temporary sender
    
    for (const string recipient : emailRecipients) {
        newEmail->addRecipient(MailRecipient(MailRecipient::PRIMARY_RECIPIENT, recipient));
    }
    
    emailSubject = MailMessage::encodeWord(emailSubject, "UTF-8");
    
    newEmail->setSubject(emailSubject);
    newEmail->setContentType("text/plain; charset=UTF-8");
    newEmail->setContent(emailContent, MailMessage::ENCODING_8BIT);

    return newEmail;
}

MailMessage * EmailMessageCreator::createEmail(vector<string> emailRecipients, string emailSubject, string emailContent, std::unordered_map<string, string> fileAttachmentMap)
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
