//
//  user_interface.hpp
//  qs
//
//  Created by Peter Xu on 4/22/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef UserInterface_hpp
#define UserInterface_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <unordered_map>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "accounts_manager.hpp"
#include "email_networking_manager.hpp"
#include "email_message_creator.hpp"
#include "qs_manager.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class UserInterface {
public:
    static int main(int argc, const char * argv[]);
    static void interactiveAddEmailAccount();
    static void interactiveDeleteEmailAccount(int argc, const char* argv[]);
    static void displayAllEmails();
};

int main(int argc, const char * argv[]);

#endif /* user_interface_hpp */
