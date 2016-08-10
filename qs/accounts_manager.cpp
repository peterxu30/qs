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
    ASSERT(isValidEmailAddress(email), "fatal: Email address is not of proper format.");
    ASSERT(verifyEmailIsValid(email, password, smtpAddress), "fatal: Failed to verify a valid email account with given information.");
    
    string encodedPassword = base64_encode(reinterpret_cast<const unsigned char*>(password.c_str()), 20);
    
    ptree account;
    account.put("address", email);
    account.put("password", encodedPassword);
    account.put("smtp", smtpAddress);
    
    ptree accountJson;
    Utilities::convertJsonToPtree(ACCOUNT_FILE_PATH, accountJson);
    
    if (active) {
        accountJson.get_child("active").clear();
        accountJson.put_child("active", account);
    }

    accountJson.get_child("accounts").push_back(std::make_pair("", account));
    Utilities::rebuildFile(ACCOUNT_FILE_PATH, accountJson);
}

bool AccountsManager::removeEmailAccount(string email) {
    ptree accountJson;
    Utilities::convertJsonToPtree(ACCOUNT_FILE_PATH, accountJson);
    if (getActiveEmailAddress() == email) {
        accountJson.put("active", "");
    }
    
    ptree& accounts = accountJson.get_child("accounts");
    for(auto it = accounts.begin(); it != accounts.end();) {
        if(it->second.get_value<string>("email") == email)
            it = accounts.erase(it);
        else
            ++it;
    }
    Utilities::rebuildFile(ACCOUNT_FILE_PATH, accountJson);
    return true;
}

AccountsManager::Account AccountsManager::getActiveEmailAccount() {
    ptree accountJson;
    Utilities::convertJsonToPtree(ACCOUNT_FILE_PATH, accountJson);
    ptree active = accountJson.get_child("active");
    if (active.get_child("address").get_value<string>() == "") {
        throw std::runtime_error("no active account selected.");
    }
    AccountsManager::Account activeAccount;
    activeAccount.email = active.get_child("address").get_value<string>();
    activeAccount.password = base64_decode(active.get_child("password").get_value<string>());
    activeAccount.smtpAddress = active.get_child("smtp").get_value<string>();
    return activeAccount;
}

list<string> AccountsManager::getAllEmailsAsStrings() {
    ptree accountJson;
    Utilities::convertJsonToPtree(ACCOUNT_FILE_PATH, accountJson);
    list<string> emailsAsStrings;

    for (auto& account : accountJson.get_child("accounts")) {
        string address = account.second.get_child("address").get_value<string>();
        emailsAsStrings.push_back(address);
    }
    
    return emailsAsStrings;
}

string AccountsManager::getActiveEmailAddress() {
    return getActiveEmailAccount().email;
}

//switch to json
void AccountsManager::switchActiveEmailAccount(string email) {
    ptree accountJson;
    Utilities::convertJsonToPtree(ACCOUNT_FILE_PATH, accountJson);
    bool exists = false;
    
    for (auto& account : accountJson.get_child("accounts")) {
        if (account.second.get_child("address").get_value<string>() == email) {
            accountJson.add_child("active", account.second);
            exists = true;
        }
    }
    
    if (!exists) {
        throw std::invalid_argument("email does not exist.");
    }
    
    Utilities::rebuildFile(ACCOUNT_FILE_PATH, accountJson);
}

bool AccountsManager::isSupportedEmailDomain(string email) {
    ASSERT(isValidEmailAddress(email), "fatal: email address is not of proper format.");
    vector<string> tokens;
    boost::algorithm::split(tokens, email, boost::algorithm::is_any_of("@"));
    string domain = tokens[1];
    if (supportedEmailDomains.find(domain) == supportedEmailDomains.end()) {
        return false;
    }
    return true;
}

string AccountsManager::getSupportedDomainSMTP(string email) {
    ASSERT(isSupportedEmailDomain(email), "fatal: Domain is not supported for automatic SMTP retrieval.");
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

void AccountsManager::rebuildAccountsFile(list<string>& fileContents) {
    Utilities::rebuildFile(ACCOUNT_FILE_PATH, fileContents);
}
