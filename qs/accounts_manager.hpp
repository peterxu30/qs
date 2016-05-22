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
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/filesystem.hpp>

#include "base64.hpp"
#include "error_checking_macros.h"

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

class AccountsManager {
public:
    struct Account {
        string email;
        string password;
        string smtpAddress;
    };
    
    static bool accountsManagerIsInitialized();
    static void addEmailAccount(string email, string password, string smtpAddress, bool active);
    static bool deleteEmailAccount(string email);
    static void deleteAllEmailAccounts();
    static AccountsManager::Account getActiveEmailAccount();
    static string getActiveEmailAddress();
    static vector<string> getAllEmailsAsStrings();
    static void switchActiveEmailAccount(string email);
private:
    static string activeEmailAddress;
    static string activeEmailEncodedPassword;
    static string activeEmailSMTP;
    static bool activeAccountExists;
    static bool verifyEmailIsValid(string email, string password, string smtpAddress);
    static void changeActiveEmailAccountVariables(string email, string encodedPassword, string emailSMTP);
    static void rebuildAccountsFile(list<string>& fileContents);
};

#endif /* accounts_manager_hpp */
