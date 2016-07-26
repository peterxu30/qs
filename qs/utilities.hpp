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
#include <unordered_map>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

namespace Utilities {
    void getFileContents(string filePath, list<string>& fileContents);
    void convertJsonToPtree(string filePath, ptree& pt);
    int rebuildFile(string filePath, list<string>& fileContents);
    int rebuildFile(string filePath, string fileContents);
    int rebuildFile(string filePath, ptree& json);
    string toLowerCase(string str);
}

#endif /* utilities_hpp */
