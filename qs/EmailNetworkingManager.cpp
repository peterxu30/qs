//
//  EmailNetworkingManager.cpp
//  qs
//
//  Created by Peter Xu on 4/22/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//
//  --Credits--
//  The majority of this code was borrowed from http://axistasoft.com/blog/poco/poco-net/item/sending-email-messages-using-poco-smtpclientsession-class and tailored to suit my purposes.
//

#include "EmailNetworkingManager.hpp"

int EmailNetworkingManager::sendEmail(MailMessage * email)
{
    cout << "HELLO!" << endl;
    string host = "smtp.gmail.com";
    UInt16 port = 465;
    string user = "atdpjava15@gmail.com";
    string password = "cupofjava";
    
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

