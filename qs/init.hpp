//
//  init.hpp
//  qs
//
//  Created by Peter Xu on 6/29/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef init_hpp
#define init_hpp

#include <stdio.h>

#include "action.hpp"
#include "qs_manager.hpp"

class Init : public Action {
public:
    void execute() override;
};

#endif /* init_hpp */
