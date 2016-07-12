//
//  accounts_manager.cpp
//  qs
//
//  Created by Peter Xu on 5/16/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "accounts_manager.hpp"

char * AccountsManager::ACCOUNT_FILE_PATH = "qs_data/accountFile.txt";

string AccountsManager::activeEmailAddress;
string AccountsManager::activeEmailEncodedPassword;
string AccountsManager::activeEmailSMTP;
bool AccountsManager::activeAccountExists = false;
std::unordered_map<string, string> AccountsManager::supportedEmailDomains {
    { "gmail.com", "smtp.gmail.com" },
    { "yahoo.com", "smtp.mail.yahoo.com"}
};

bool AccountsManager::accountsManagerIsInitialized() {
    return boost::filesystem::exists(ACCOUNT_FILE_PATH);
}

void AccountsManager::addEmailAccount(string email, string password, string smtpAddress, bool active) {
    ASSERT(isValidEmailAddress(email), "Fatal: Email address is not of proper format.");
    ASSERT(verifyEmailIsValid(email, password, smtpAddress), "Add failed: Failed to verify a valid email account with given information.");
    
    string encodedPassword = base64_encode(reinterpret_cast<const unsigned char*>(password.c_str()), 20);
    
    list<string> fileContents;
    Utilities::getFileContents(ACCOUNT_FILE_PATH, fileContents);
    list<string> updatedFileContents;
    for (string accountLine : fileContents) {
        vector<string> tokens;
        boost::algorithm::split(tokens, accountLine, boost::algorithm::is_any_of(" "));
        
        if (active && tokens.size() == 4) {
            size_t len = accountLine.size();
            accountLine.erase(len-1, 2);
        }
        
        if (email != tokens[0]) {
            updatedFileContents.push_back(accountLine);
        }
    }
    
    if (active) {
        updatedFileContents.push_front(email + " " + encodedPassword + " " + smtpAddress + " *");
        changeActiveEmailAccountVariables(email, encodedPassword, smtpAddress);
    } else {
        updatedFileContents.push_back(email + " " + encodedPassword + " " + smtpAddress);
    }
    
    rebuildAccountsFile(updatedFileContents);
}

bool AccountsManager::deleteEmailAccount(string email) {
    list<string> fileContents;
    Utilities::getFileContents(ACCOUNT_FILE_PATH, fileContents);
    list<string> updatedFileContents;
    bool deleted = false;
    for (string accountLine : fileContents) {
        vector<string> tokens;
        boost::algorithm::split(tokens, accountLine, boost::algorithm::is_any_of(" "));
        
        if (email == tokens[0]) {
            if (tokens.size() == 4) {
                AccountsManager::activeAccountExists = false;
            }
            deleted = true;
        } else {
            updatedFileContents.push_back(accountLine);
        }
    }
    
    rebuildAccountsFile(updatedFileContents);
    return deleted;
}

AccountsManager::Account AccountsManager::getActiveEmailAccount() {
    list<string> fileContents;
    Utilities::getFileContents(ACCOUNT_FILE_PATH, fileContents);
    bool activeExists = false;
    if (!AccountsManager::activeAccountExists) {
        for (string accountLine : fileContents) {
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
    ASSERT((activeAccountExists || activeExists), "fatal: No active account selected.");
    
    activeAccount.email = activeEmailAddress;
    activeAccount.password = base64_decode(activeEmailEncodedPassword);
    activeAccount.smtpAddress = activeEmailSMTP;
    
    return activeAccount;
}

list<string> AccountsManager::getAllEmailsAsStrings() {
    list<string> fileContents;
    Utilities::getFileContents(ACCOUNT_FILE_PATH, fileContents);

    list<string> emailsAsStrings;
    for (string accountLine : fileContents) {
        vector<string> tokens;
        boost::algorithm::split(tokens, accountLine, boost::algorithm::is_any_of(" "));
        
        string accountWithoutPassword;
        if (tokens.size() == 4) {
            accountWithoutPassword = "* " + tokens[0];
        } else {
            accountWithoutPassword = tokens[0];
        }
        
        emailsAsStrings.push_back(accountWithoutPassword);
    }
    return emailsAsStrings;
}

string AccountsManager::getActiveEmailAddress() {
    return getActiveEmailAccount().email;
}

void AccountsManager::switchActiveEmailAccount(string email) {
    std::ifstream accountsFileStream(ACCOUNT_FILE_PATH);
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
    ASSERT(isValidEmailAddress(email), "fatal: Email address is not of proper format.");
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

//needs work
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

//unneccessary?
void AccountsManager::changeActiveEmailAccountVariables(string email, string encodedPassword, string emailSMTP) {
    AccountsManager::activeEmailAddress = email;
    AccountsManager::activeEmailEncodedPassword = encodedPassword;
    AccountsManager::activeEmailSMTP = emailSMTP;
    AccountsManager::activeAccountExists = true;
}

void AccountsManager::rebuildAccountsFile(list<string>& fileContents) {
    Utilities::rebuildFile("qs_data/accountFile.txt", fileContents);
}
