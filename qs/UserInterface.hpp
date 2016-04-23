//
//  UserInterface.hpp
//  qs
//
//  Created by Peter Xu on 4/22/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef UserInterface_hpp
#define UserInterface_hpp

#include <stdio.h>
#include <iostream>
#include <string>

#include "EmailNetworkingManager.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class UserInterface
{
public:
    static int main(int argc, const char * argv[]);
};

int main(int argc, const char * argv[]);

#endif /* UserInterface_hpp */
