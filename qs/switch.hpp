//
//  switch.hpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef switch_hpp
#define switch_hpp

#include <stdio.h>
#include <iostream>

#include "action.hpp"
#include "accounts_manager.hpp"

using std::cout;

class Switch : public Action {
public:
    void execute() override;
};

#endif /* switch_hpp */
