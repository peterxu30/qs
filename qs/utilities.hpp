//
//  utilities.hpp
//  qs
//
//  Created by Peter Xu on 6/5/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef utilities_hpp
#define utilities_hpp

#include <stdio.h>
#include <list>
#include <fstream>
#include <istream>
#include <iostream>

#include <boost/filesystem.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

namespace Utilities {
    void getFileContents(string filePath, list<string>& fileContents);
    int rebuildFile(const char * filePath, list<string>& fileContents);
    string toLowerCase(string str);
}

#endif /* utilities_hpp */
