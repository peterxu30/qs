//
//  AccountsManager.cpp
//  qs
//
//  Created by Peter Xu on 5/16/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "AccountsManager.hpp"

void AccountsManager::initializeQuickSendAccountsManager() {
    std::ofstream accountFile("qs/accountFile.txt");
    const char dir_path[] = "qs_data";
    
    boost::filesystem::path dir(dir_path);
    if(boost::filesystem::create_directory(dir)) {
        std::cout << "Success" << "\n";
    }
}