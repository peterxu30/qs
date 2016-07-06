//
//  user_interface.cpp
//  qs
//
//  Created by Peter Xu on 4/22/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "user_interface.hpp"

int UserInterface::main(int argc, const char * argv[]) {
    // list<tokens> tokens = Tokenizer::tokenize(argc, argv);
    
    if (argc > 1) {
        string command = argv[1];
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        
        if (command == "init") {
            QSManager::initializeQuickSend();
        } else if (command == "new") {
            if (argc == 4) {
                string emailType = argv[2];
                if (emailType == "msg") {
                    
                } else if (emailType == "file") {
                    
                } else if (emailType == "full") {
                    
                } else {
                    cout << "Command failed: " << emailType <<
                    " is not an accepted message type." << endl;
                }
            } else {
                cout << "Command failed: " << "Unacceptable amount of arguments." << endl;
            }
        } else if (command == "add") {
            interactiveAddEmailAccount();
        } else if (command == "clear") {
            
        } else if (command == "log") {
            displayAllEmailMessages();
        } else if (command == "switch") {
            
        } else if (command == "rm") {
            interactiveDeleteEmailAccount(argc, argv);
        } else {
            cout << "Command failed: " << command << " is not a qs command." << endl;
        }
    } else {
        cout << "No command entered." << endl;
    }
    return 0;
}

void UserInterface::interactiveAddEmailAccount() {
    ASSERT(QSManager::dataDirectoryInitialized(), "Add Failed: QuickSend is not initialized.");
    ASSERT(AccountsManager::accountsManagerIsInitialized(), "Add failed: accountsFile does not exist.");
    
    string email;
    string password;
    string smtpAddress;
    string setActive;
    bool active = false;
    cout << "Add new email account.\n";
    
    cout << "Email: ";
    cin >> email;
    
    cout << "Password: ";
    cin >> password;
    
//    doesn't work yet.
//    if (AccountsManager::isSupportedEmailDomain(email)) {
//        smtpAddress = AccountsManager::getSupportedDomainSMTP(email);
//        cout << "SMTP Address: " << smtpAddress << '\r';
//        string s = "SMTP Address: " + smtpAddress;
//        
//        move(tgetnum("li"), s.size());
//        refresh();
////        move(1, 1);
//        
//        string dummy;
//        string inputSMTP;
//        getline(cin, dummy);
//        getline(cin, inputSMTP);
//        
//        if (inputSMTP != "\0") {
//            smtpAddress = inputSMTP;
//        }
//    } else {
//        cout << "SMTP Address: ";
//        cin >> smtpAddress;
//    }
    
    cout << "SMTP Address: ";
    cin >> smtpAddress;
    
    cout << "Set to active account? (y/n): ";
    cin >> setActive;
    std::transform(setActive.begin(), setActive.end(), setActive.begin(), ::tolower);
    
    if (setActive == "y") {
        active = true;
    }
    
    AccountsManager::addEmailAccount(email, password, smtpAddress, active);
    cout << "Account saved." << endl;
}

void UserInterface::interactiveDeleteEmailAccount(int argc, const char* argv[]) {
    if (argc == 3) {
        if (AccountsManager::deleteEmailAccount(argv[2])) {
            cout << "Email deleted." << endl;
        } else {
            cout << "Delete failed: Email not found." << endl;
        }
    } else {
        cout << "Delete failed: Improper amount of arguments." << endl;
    }
}

void UserInterface::interactiveNewEmail(int argc, const char * argv[]) {
    if (argc == 3) {
        if (argv[2] == "msg") { //just msg
            
        } else if (argv[2] == "file") { //just attachment
            
        } else if (argv[2] == "full") { //msg + attachment
            
        }
    }
}

void UserInterface::displayAllEmailAddresses() {
    list<string> emailsAsStrings = AccountsManager::getAllEmailsAsStrings();
    
    cout << "Email Address  |  SMTP Address\n";
    for (string emailAddress : emailsAsStrings) {
        cout << emailAddress << '\n';
    }
    cout << endl;
}

void UserInterface::displayAllEmailMessages() {
    list<string> emailMessages = EmailManager::getAllSentMessages();
    
    cout << "Message Log\n";
    for (string emailMessage : emailMessages) {
        cout << emailMessage << '\n';
    }
    cout << endl;
}

//void UserInterface::createNewEmail

int main(int argc, const char * argv[]) {
    string cwd = getcwd(NULL, 0); //current working directory
    cout << cwd << endl;
//
//    vector<string> to = {"peterxu30@berkeley.edu"};
//    
//    //Test
//    std::unordered_map<string, string> attachments;
////    attachments["qs"] = "qs";
////    attachments["qs1"] = "qs";
//    
//    MailMessage * email = EmailMessageCreator::createEmail(to, "Test Email", "Hello!", attachments);
////    EmailNetworkingManager::sendEmail(email);
//    
//    delete email;
    list<Token *> tokens = Tokenizer::tokenize(argc, argv);
    Interpreter::eval(tokens);
//    return UserInterface::main(argc, argv);
}
