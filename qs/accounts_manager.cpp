//
//  accounts_manager.cpp
//  qs
//
//  Created by Peter Xu on 5/16/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "accounts_manager.hpp"

string AccountsManager::activeEmailAddress;
string AccountsManager::activeEmailPasswordHashed;
string AccountsManager::activeEmailSMTP;

void AccountsManager::initializeQuickSendAccountsManager() {
    ASSERT(!accountsManagerIsInitialized(), "Initialization failed: quicksend is already initialized.");
    
    const char dir_path[] = "qs_data";
    boost::filesystem::path dir(dir_path);
    
    if(boost::filesystem::create_directory(dir)) {
        std::ofstream accountFile("qs_data/accountFile.txt");
        cout << "quicksend initialized." << "\n";
        interactiveAddEmailAccount();
    } else {
        cout << "Unable to create quicksend directory during initialization." << endl;
    }
}

void AccountsManager::interactiveAddEmailAccount() {
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
    
    cout << "SMTP Address: ";
    cin >> smtpAddress;
    
    cout << "Set to active account? (y/n): ";
    cin >> setActive;
    std::transform(setActive.begin(), setActive.end(), setActive.begin(), ::tolower);
    cout << setActive.length();
    if (setActive == "y") {
        active = true;
        cout << "I'm real";
    }
    
    cout << "Verifying all information is correct...\n";
    if (verifyEmailIsValid(email, password, smtpAddress)) {
        cout << "Information verified.\n";
        addEmailAccount(email, password, smtpAddress, active);
        cout << "Account saved." << endl;
    } else {
        cout << "Information invalid. Account not saved." << endl;
    }
}

void AccountsManager::addEmailAccount(string email, string password, string smtpAddress, bool active) {
    ASSERT(accountsManagerIsInitialized(), "Email not added: quicksend is not initialized.");
    
//    string hashedPassword = 
    
    std::ifstream accountsFile("qs_data/accountFile.txt");
    list<string> fileContents;
    string accountLine;
    bool exists = false;
    if (accountsFile.is_open()) {
        while (getline(accountsFile, accountLine, '\n')) {
            vector<string> tokens;
            boost::algorithm::split(tokens, accountLine, boost::algorithm::is_any_of(" "));
            
            if (active && tokens.size() == 4) {
                size_t len = accountLine.size();
                accountLine.erase(len-1, 2);
            }
            
            if (email == tokens[0]) {
                cout << "Account already exists." << endl;
                exists = true;
                accountLine += " *";
                fileContents.push_front(accountLine);
            } else {
                fileContents.push_back(accountLine);
            }
        }
    }
    
    if (!exists) {
        fileContents.push_front(email + " " + password + " " + smtpAddress + " *");
    }
    
    if (active) {
        AccountsManager::activeEmailAddress = email;
        AccountsManager::activeEmailPasswordHashed = password;
        AccountsManager::activeEmailSMTP = smtpAddress;
    }
    rebuildAccountsFile(fileContents);
}

void AccountsManager::switchActiveEmailAccount(string email) {
    std::ifstream accountsFile("qs_data/accountFile.txt");
    list<string> fileContents;
    string accountLine;
    bool exists = false;
    if (accountsFile.is_open()) {
        while (getline(accountsFile, accountLine, '\n')) {
            vector<string> tokens;
            boost::algorithm::split(tokens, accountLine, boost::algorithm::is_any_of(" "));
            
            if (tokens.size() == 4) {
                size_t len = accountLine.size();
                accountLine.erase(len-1, 2);
            }
            
            if (email == tokens[0]) {
                exists = true;
                accountLine += " *";
                fileContents.push_front(accountLine);
                
                AccountsManager::activeEmailAddress = tokens[0];
                AccountsManager::activeEmailPasswordHashed = tokens[1];
                AccountsManager::activeEmailSMTP = tokens[3];
            } else {
                fileContents.push_back(accountLine);
            }
        }
    }
    if (!exists) {
        cout << "Switch failed: Account does not exist." << endl;
    }
    rebuildAccountsFile(fileContents);
}

bool AccountsManager::accountsManagerIsInitialized() {
    return boost::filesystem::exists("qs_data/accountFile.txt");
}

bool AccountsManager::verifyEmailIsValid(string email, string password, string smptpAddress) {
    return true;
}

void AccountsManager::rebuildAccountsFile(list<string>& fileContents) {
    std::fstream accountsFile("qs_data/accountFile.txt");
    if (accountsFile.is_open()) {
        list<string>::iterator iter = fileContents.begin();
        list<string>::iterator end = fileContents.end();
        while (iter != end) {
            accountsFile << *iter << '\n';
            ++iter;
        }
    }
}
