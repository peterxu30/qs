//
//  qs_manager.hpp
//  qs
//
//  Created by Peter Xu on 5/19/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef qs_manager_hpp
#define qs_manager_hpp

#include <stdio.h>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "accounts_manager.hpp"
#include "email_manager.hpp"
#include "error_checking_macros.h"
#include "log_manager.hpp"
#include "user_interface.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

class QSManager {
public:
    static void initializeQuickSend();
    static bool dataDirectoryInitialized();
};

#endif /* qs_manager_hpp */
