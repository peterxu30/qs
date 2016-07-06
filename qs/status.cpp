//
//  status.cpp
//  qs
//
//  Created by Peter Xu on 7/5/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "status.hpp"

void Status::execute() {
    unordered_map<string, string> stagedFiles;
    EmailManager::getAllStagedFiles(stagedFiles);
    std::cout << stagedFiles.size() << " files staged";
    for (auto kv : stagedFiles) {
        string filePath = kv.second;
        std::cout << "\n" << filePath;
    }
    std::cout << endl;
}