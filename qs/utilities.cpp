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

void Utilities::convertJsonToPtree(string filePath, ptree pt) {
    list<string> fileContents;
    getFileContents(filePath, fileContents);
    string json = fileContents.front();
    cout << json;\
    std::istringstream jsonStream(json);
    read_json(jsonStream, pt);
}


int Utilities::rebuildFile(string filePath, list<string>& fileContents) {
    FILE* accountsFile;
    accountsFile = fopen(filePath.c_str(), "w");
    
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

int Utilities::rebuildFile(string filePath, string fileContents) {
    list<string> temporary;
    temporary.push_back(fileContents);
    return rebuildFile(filePath, temporary);
}

string Utilities::toLowerCase(string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
