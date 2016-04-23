//
//  EmailNetworkingManager.cpp
//  qs
//
//  Created by Peter Xu on 4/22/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "EmailNetworkingManager.hpp"

int EmailNetworkingManager::sendEmail(vector<string> emailRecipients, string emailSubject, string emailBody)
{
    cout << "HELLO!" << endl;
    string host = "smtp.gmail.com";
    UInt16 port = 465;
    string user = "atdpjava15@gmail.com";
    string password = "cupofjava";
    string from = "atdpjava15@gmail.com";
    string subject = emailSubject;
    subject = MailMessage::encodeWord(subject, "UTF-8");
    string content = emailBody;
    
    MailMessage message;
    message.setSender(from);
    
    for (const string recipient : emailRecipients) {
        message.addRecipient(MailRecipient(MailRecipient::PRIMARY_RECIPIENT, recipient));
    }
    
    message.setSubject(subject);
    message.setContentType("text/plain; charset=UTF-8");
    message.setContent(content, MailMessage::ENCODING_8BIT);
    
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
            session.sendMessage(message);
            cout << "Message successfully sent" << endl;
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
