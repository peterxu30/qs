//
//  utilities.cpp
//  qs
//
//  Created by Peter Xu on 6/5/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "utilities.hpp"

int Utilities::rebuildFile(char * filePath, list<string>& fileContents) {
    FILE* accountsFile;
    accountsFile = fopen(filePath, "w");
    
    std::fstream accountsFileStream(filePath);
    if (accountsFileStream.is_open()) {
        list<string>::iterator iter = fileContents.begin();
        list<string>::iterator end = fileContents.end();
        while (iter != end) {
            accountsFileStream << *iter << '\n';
            ++iter;
        }
    } else {
        return 1;
    }
    return 0;
}