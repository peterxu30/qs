//
//  AccountsManager.hpp
//  qs
//
//  Created by Peter Xu on 5/16/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef AccountsManager_hpp
#define AccountsManager_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>

#include <boost/filesystem.hpp>

using std::string;

class AccountsManager {
public:
    static void initializeQuickSendAccountsManager();
    static void addEmailAccount(string username, string password, string smtpAddress);
    static void deleteEmailAccount(string username);
    static void deleteAllEmailAccounts();
    static string getActiveEmailAccount();
    static void switchActiveEmailAccount(string username);
};

#endif /* AccountsManager_hpp */
