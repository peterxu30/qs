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
#include "error_checking_macros.h"

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

class AccountsManager {
public:
    static void initializeQuickSendAccountsManager();
    static void addEmailAccount(string email, string password, string smtpAddress, bool active);
    static void interactiveAddEmailAccount();
    static void deleteEmailAccount(string email);
    static void deleteAllEmailAccounts();
    static string getActiveEmailAccount();
    static void switchActiveEmailAccount(string email);
private:
    static string activeEmailAddress;
    static string activeEmailPasswordHashed;
    static string activeEmailSMTP;
    static bool accountsManagerIsInitialized();
    static bool verifyEmailIsValid(string email, string password, string smtpAddress);
    static void rebuildAccountsFile(list<string>& fileContents);
};

#endif /* accounts_manager_hpp */
