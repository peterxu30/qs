//
//  accounts_manager.hpp
//  qs
//
//  Created by Peter Xu on 5/16/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef accounts_manager_hpp
#define accounts_manager_hpp

#include <stdio.h>
#include <list>
#include <fstream>
#include <istream>
#include <iostream>
#include <set> // replace with map.
#include <unordered_map>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/filesystem.hpp>

#include "base64.hpp"
#include "error_checking_macros.h"
#include "utilities.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::set;
using std::string;
using std::vector;

//prime candidate for singleton
class AccountsManager {
public:
    struct Account {
        string email;
        string password;
        string smtpAddress;
    };
    
    static bool accountsManagerIsInitialized();
    static void addEmailAccount(string email, string password, string smtpAddress, bool active);
    static bool removeEmailAccount(string email);
    static void removeAllEmailAccounts();
    static AccountsManager::Account getActiveEmailAccount();
    static string getActiveEmailAddress();
    static list<string> getAllEmailsAsStrings();
    static void switchActiveEmailAccount(string email);
    static bool isSupportedEmailDomain(string email);
    static string getSupportedDomainSMTP(string email);
private:
    static char * ACCOUNT_FILE_PATH;
    static string activeEmailAddress;
    static string activeEmailEncodedPassword;
    static string activeEmailSMTP;
    static bool activeAccountExists;
    static std::unordered_map<string, string> supportedEmailDomains;
    static bool verifyEmailIsValid(string email, string password, string smtpAddress);
    static bool isValidEmailAddress(string email);
    static void rebuildAccountsFile(list<string>& fileContents);
};

#endif /* accounts_manager_hpp */
