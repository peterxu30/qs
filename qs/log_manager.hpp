//
//  log_manager.hpp
//  qs
//
//  Created by Peter Xu on 5/19/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef log_manager_hpp
#define log_manager_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "utilities.hpp"

using std::string;
using std::vector;

class LogManager {
public:
    static bool logIsInitialized();
    static void logEmail(string sender, list<string> emailRecipients, string emailSubject, string emailContent);
    static void logEmail(string sender, list<string> emailRecipients, string emailSubject, string emailContent, std::unordered_map<string, string> fileAttachmentMap);
    static list<string> getAllSentMessages();
    
private:
    static char * LOG_FILE_PATH;
    static char * LOG_DIR_PATH;
    static void addEmailToLog(string fileName);

};

#endif /* log_manager_hpp */
