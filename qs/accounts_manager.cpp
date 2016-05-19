//
//  accounts_manager.cpp
//  qs
//
//  Created by Peter Xu on 5/16/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "accounts_manager.hpp"

string AccountsManager::activeEmailAddress;
string AccountsManager::activeEmailEncodedPassword;
string AccountsManager::activeEmailSMTP;
bool AccountsManager::activeAccountExists = false;

// this method subject to change after more features implemented.
void AccountsManager::initializeQuickSendAccountsManager() {
    ASSERT(!accountsManagerIsInitialized(), "Initialization failed: quicksend is already initialized.");
    
    const char dir_path[] = "qs_data";
    boost::filesystem::path dir(dir_path);
    
    if(boost::filesystem::create_directory(dir)) {
        std::ofstream accountFile("qs_data/accountFile.txt");
        cout << "quicksend initialized." << "\n";
        interactiveAddEmailAccount();
    } else {
        cout << "Initialization failed: Unable to create quicksend directory during initialization." << endl;
    }
}

void AccountsManager::addEmailAccount(string email, string password, string smtpAddress, bool active) {
    ASSERT(accountsManagerIsInitialized(), "Email not added: quicksend is not initialized.");
    
    string encodedPassword = base64_encode(reinterpret_cast<const unsigned char*>(password.c_str()), 20);
    
    std::ifstream accountsFile("qs_data/accountFile.txt");
    list<string> fileContents;
    string accountLine;
    if (accountsFile.is_open()) {
        while (getline(accountsFile, accountLine, '\n')) {
            vector<string> tokens;
            boost::algorithm::split(tokens, accountLine, boost::algorithm::is_any_of(" "));
            
            if (active && tokens.size() == 4) {
                size_t len = accountLine.size();
                accountLine.erase(len-1, 2);
            }
            
            if (email != tokens[0]) {
                fileContents.push_back(accountLine);
            }
        }
    }
    
    if (active) {
        fileContents.push_front(email + " " + encodedPassword + " " + smtpAddress + " *");
        changeActiveEmailAccountVariables(email, encodedPassword, smtpAddress);
    } else {
        fileContents.push_front(email + " " + encodedPassword + " " + smtpAddress);
    }
    
    rebuildAccountsFile(fileContents);
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
    }
    
    cout << "Verifying all information is correct...\n";
    if (verifyEmailIsValid(email, password, smtpAddress)) {
        cout << "Information verified.\n";
        addEmailAccount(email, password, smtpAddress, active);
        cout << "Account saved." << endl;
    } else {
        cout << "Account not saved: Information invalid." << endl;
    }
}

bool AccountsManager::deleteEmailAccount(string email) {
    std::ifstream accountsFile("qs_data/accountFile.txt");
    list<string> fileContents;
    string accountLine;
    bool deleted = false;
    if (accountsFile.is_open()) {
        while (getline(accountsFile, accountLine, '\n')) {
            vector<string> tokens;
            boost::algorithm::split(tokens, accountLine, boost::algorithm::is_any_of(" "));
            
            if (email == tokens[0]) {
                if (tokens.size() == 4) {
                    AccountsManager::activeAccountExists = false;
                }
                deleted = true;
            } else {
                fileContents.push_back(accountLine);
            }
        }
    }

    rebuildAccountsFile(fileContents);
    return deleted;
}

void AccountsManager::interactiveDeleteEmailAccount() {
    string email;
    cout << "Delete email account.\n";
    
    cout << "Email Address: ";
    cin >> email;
    
    if (deleteEmailAccount(email)) {
        cout << "Account deleted." << endl;
    } else {
        cout << "Delete failed: Account not found." << endl;
    }
    
}

AccountsManager::Account AccountsManager::getActiveEmailAccount() {
    std::ifstream accountsFile("qs_data/accountFile.txt");
    string accountLine;
    bool activeExists = false;
    if (!AccountsManager::activeAccountExists && accountsFile.is_open()) {
        while (getline(accountsFile, accountLine, '\n')) {
            vector<string> tokens;
            boost::algorithm::split(tokens, accountLine, boost::algorithm::is_any_of(" "));
            
            if (tokens.size() == 4) {
                activeEmailAddress = tokens[0];
                activeEmailEncodedPassword = tokens[1];
                activeEmailSMTP = tokens[2];
                activeExists = true;
                break;
            }
        }
    }
    
    AccountsManager::Account activeAccount;
    
    if (!AccountsManager::activeAccountExists && !activeExists) {
        cout << "Failure: No active account selected.";
        
        activeAccount.email = "NULL";
        activeAccount.password = "NULL";
        activeAccount.smtpAddress = "NULL";
    } else {
        activeAccount.email = activeEmailAddress;
        activeAccount.password = base64_decode(activeEmailEncodedPassword);
        activeAccount.smtpAddress = activeEmailSMTP;
    }
    return activeAccount;
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
                
                changeActiveEmailAccountVariables(tokens[0], tokens[1], tokens[2]);
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

void AccountsManager::changeActiveEmailAccountVariables(string email, string encodedPassword, string emailSMTP) {
    AccountsManager::activeEmailAddress = email;
    AccountsManager::activeEmailEncodedPassword = encodedPassword;
    AccountsManager::activeEmailSMTP = emailSMTP;
    AccountsManager::activeAccountExists = true;
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
