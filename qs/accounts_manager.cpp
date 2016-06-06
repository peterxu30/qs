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
std::unordered_map<string, string> AccountsManager::supportedEmailDomains {
    { "gmail.com", "smtp.gmail.com" },
    { "yahoo.com", "smtp.mail.yahoo.com"}
};

bool AccountsManager::accountsManagerIsInitialized() {
    return boost::filesystem::exists("qs_data/accountFile.txt");
}

void AccountsManager::addEmailAccount(string email, string password, string smtpAddress, bool active) {
    ASSERT(isValidEmailAddress(email), "Add failed: Email address is not of proper format.");
    ASSERT(verifyEmailIsValid(email, password, smtpAddress), "Add failed: Failed to verify a valid email account with given information.");
    
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
        fileContents.push_back(email + " " + encodedPassword + " " + smtpAddress);
    }
    
    rebuildAccountsFile(fileContents);
}

bool AccountsManager::deleteEmailAccount(string email) {
    std::ifstream accountsFileStream("qs_data/accountFile.txt");
    list<string> fileContents;
    string accountLine;
    bool deleted = false;
    if (accountsFileStream.is_open()) {
        while (getline(accountsFileStream, accountLine, '\n')) {
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

AccountsManager::Account AccountsManager::getActiveEmailAccount() {
    std::ifstream accountsFileStream("qs_data/accountFile.txt");
    string accountLine;
    bool activeExists = false;
    if (!AccountsManager::activeAccountExists && accountsFileStream.is_open()) {
        while (getline(accountsFileStream, accountLine, '\n')) {
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
    ASSERT((activeAccountExists || activeExists), "Failure: No active account selected.");
    
    activeAccount.email = activeEmailAddress;
    activeAccount.password = base64_decode(activeEmailEncodedPassword);
    activeAccount.smtpAddress = activeEmailSMTP;
    
//    if (!AccountsManager::activeAccountExists && !activeExists) {
//        cout << "Failure: No active account selected.";
//        
//        activeAccount.email = "NULL";
//        activeAccount.password = "NULL";
//        activeAccount.smtpAddress = "NULL";
//    } else {
//        activeAccount.email = activeEmailAddress;
//        activeAccount.password = base64_decode(activeEmailEncodedPassword);
//        activeAccount.smtpAddress = activeEmailSMTP;
//    }
    return activeAccount;
}

vector<string> AccountsManager::getAllEmailsAsStrings() {
    std::ifstream accountsFileStream("qs_data/accountFile.txt");
    string accountLine;
    vector<string> emailsAsStrings;
    if (accountsFileStream.is_open()) {
        while (getline(accountsFileStream, accountLine, '\n')) {
            vector<string> tokens;
            boost::algorithm::split(tokens, accountLine, boost::algorithm::is_any_of(" "));
            
            string accountWithoutPassword;
            if (tokens.size() == 4) {
                accountWithoutPassword = tokens[0] + " " + tokens[2] + " *";
            } else {
                accountWithoutPassword = tokens[0] + " " + tokens[2];
            }
            
            emailsAsStrings.push_back(accountWithoutPassword);
        }
    }
    return emailsAsStrings;
}

string AccountsManager::getActiveEmailAddress() {
    return getActiveEmailAccount().email;
}

void AccountsManager::switchActiveEmailAccount(string email) {
    std::ifstream accountsFileStream("qs_data/accountFile.txt");
    list<string> fileContents;
    string accountLine;
    bool exists = false;
    if (accountsFileStream.is_open()) {
        while (getline(accountsFileStream, accountLine, '\n')) {
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

bool AccountsManager::isSupportedEmailDomain(string email) {
    ASSERT(isValidEmailAddress(email), "Add failed: Email address is not of proper format.");
    vector<string> tokens;
    boost::algorithm::split(tokens, email, boost::algorithm::is_any_of("@"));
    string domain = tokens[1];
    if (supportedEmailDomains.find(domain) == supportedEmailDomains.end()) {
        return false;
    }
    return true;
}

string AccountsManager::getSupportedDomainSMTP(string email) {
    ASSERT(isSupportedEmailDomain(email), "Illegal call: Domain is not supported for automatic SMTP retrieval.");
    vector<string> tokens;
    boost::algorithm::split(tokens, email, boost::algorithm::is_any_of("@"));
    return supportedEmailDomains.at(tokens[1]);
}

bool AccountsManager::verifyEmailIsValid(string email, string password, string smptpAddress) {
    return true;
}

bool AccountsManager::isValidEmailAddress(string email) {
    vector<string> tokens;
    size_t atSymbolCount = std::count(email.begin(), email.end(), '@');
    if (atSymbolCount == 1) {
        return true;
    }
    return false;
}

void AccountsManager::changeActiveEmailAccountVariables(string email, string encodedPassword, string emailSMTP) {
    AccountsManager::activeEmailAddress = email;
    AccountsManager::activeEmailEncodedPassword = encodedPassword;
    AccountsManager::activeEmailSMTP = emailSMTP;
    AccountsManager::activeAccountExists = true;
}

void AccountsManager::rebuildAccountsFile(list<string>& fileContents) {
    
    Utilities::rebuildFile("qs_data/accountFile.txt", fileContents);
    
//    FILE* accountsFile;
//    accountsFile = fopen("qs_data/accountFile.txt", "w");
//    
//    std::fstream accountsFileStream("qs_data/accountFile.txt");
//    if (accountsFileStream.is_open()) {
//        list<string>::iterator iter = fileContents.begin();
//        list<string>::iterator end = fileContents.end();
//        while (iter != end) {
//            accountsFileStream << *iter << '\n';
//            ++iter;
//        }
//    }
}
