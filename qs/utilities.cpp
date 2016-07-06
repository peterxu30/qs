//
//  utilities.cpp
//  qs
//
//  Created by Peter Xu on 6/5/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "utilities.hpp"

void Utilities::getFileContents(string filePath, list<string>& fileContents) {
    std::fstream fileStagerStream(filePath);
    string stageFileLine;
    if (fileStagerStream.is_open()) {
        while (getline(fileStagerStream, stageFileLine, '\n')) {
            fileContents.push_back(stageFileLine);
        }
    }
}

int Utilities::rebuildFile(const char * filePath, list<string>& fileContents) {
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
