//
//  user_interface.cpp
//  qs
//
//  Created by Peter Xu on 4/22/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "user_interface.hpp"

int UserInterface::main(int argc, const char * argv[]) {
    if (argc > 1) {
        string command = argv[1];
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        
        if (command == "init") {
            AccountsManager::initializeQuickSendAccountsManager();
        } else if (command == "add") {
            AccountsManager::interactiveAddEmailAccount();
        } else if (command == "rm") {
            cout << "Removed" << endl;
        } else if (command == "new") {
            cout << "New Email" << endl;
        } else if (command == "dl") {
            cout << "File downloaded." << endl;
        } else if (command == "login") {
            cout << "Login" << endl;
        } else {
            cout << command << " is not a qs command." << endl;
        }
    } else {
        cout << "No command entered." << endl;
    }
    return 0;
}

//void initializeQuickSend() {
//    ASSERT(!AccountsManager::accountsManagerIsInitialized(), "Initialization failed: quicksend is already initialized.");
//    
//    const char dir_path[] = "qs_data";
//    boost::filesystem::path dir(dir_path);
//    
//    if(boost::filesystem::create_directory(dir)) {
//        std::ofstream accountFile("qs_data/accountFile.txt");
//        cout << "quicksend initialized." << "\n";
//        interactiveAddEmailAccount();
//    } else {
//        cout << "Initialization failed: Unable to create quicksend directory during initialization." << endl;
//    }
//}

int main(int argc, const char * argv[]) {
    string cwd = getcwd(NULL, 0); //current working directory
    cout << cwd << endl;
    
    vector<string> to = {"peterxu30@gmail.com", "peterxu30@berkeley.edu"};
    
    //Test
    std::unordered_map<string, string> attachments;
    attachments["qs"] = "qs";
    attachments["qs1"] = "qs";
    
    MailMessage * email = EmailMessageCreator::createEmail(to, "Test Email", "Hello!", attachments);
    EmailNetworkingManager::sendEmail(email);
    
    delete email;
    return UserInterface::main(argc, argv);
}