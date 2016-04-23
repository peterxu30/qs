//
//  UserInterface.cpp
//  qs
//
//  Created by Peter Xu on 4/22/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#include "UserInterface.hpp"

int UserInterface::main(int argc, const char * argv[]) {
    if (argc > 1) {
        string command = argv[1];
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        
        if (command == "add") {
            cout << "Added" << endl;
        } else if (command == "rm") {
            cout << "Removed" << endl;
        } else if (command == "new") {
            cout << "New Email" << endl;
        } else if (command == "dl") {
            cout << "File downloaded." << endl;
        } else if (command == "login") {
            cout << "Login" << endl;
        } else {
            cout << command << " is not a qs command." << endl;
        }
    } else {
        cout << "No command entered." << endl;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    string cwd = getcwd(NULL, 0); //current working directory
    cout << cwd << endl;
    vector<string> to = {"peterxu30@gmail.com", "peterxu30@berkeley.edu"};
    EmailNetworkingManager().sendEmail(to, "Test Email", "Hello!");
    return UserInterface::main(argc, argv);
}