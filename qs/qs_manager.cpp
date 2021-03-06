//
//  qs_manager.cpp
//  qs
//
//  Created by Peter Xu on 5/19/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "qs_manager.hpp"

void QSManager::initializeQuickSend() {
    
    bool qsInitialized = dataDirectoryInitialized();
    if (!qsInitialized) {
        const char dir_path[] = "qs_data";
        boost::filesystem::path dir(dir_path);
        
        if (boost::filesystem::create_directory(dir)) {
            cout << "No directory detected: Data directory created.\n";
        }
    }
    
    if (!AccountsManager::accountsManagerIsInitialized()) {
        ptree temp;
        temp.put("active", "");
        temp.put("accounts", "");
        Utilities::rebuildFile("qs_data/accountFile.txt", temp);
        cout << "No account file detected: Account file created.\n";
    }
    
    if (!LogManager::logIsInitialized()) {
        const char logDirectoryPath[] = "qs_data/log";
        ptree temp;
        temp.put("files", "");
        boost::filesystem::path logDir(logDirectoryPath); //fix ghetto
        boost::filesystem::create_directory(logDir);
        Utilities::rebuildFile("qs_data/log.txt", temp);
        cout << "No log file detected: Log file created.\n";
    }
    
    if (!EmailManager::fileStagerIsInitialized()) {
        fopen("qs_data/stage.txt", "w");
        cout << "No staging file detected: File stager created.\n";

    }
    
    if(dataDirectoryInitialized()) {
        cout << "quicksend initialized." << endl;
    } else {
        cout << "fatal: Unable to create quicksend directory during initialization." << endl;
    }
}

bool QSManager::dataDirectoryInitialized() {
    return boost::filesystem::exists("qs_data");
}
