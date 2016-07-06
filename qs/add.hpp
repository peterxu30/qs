//
//  add.hpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef add_hpp
#define add_hpp

#include <stdio.h>

#include "action.hpp"
#include "email_manager.hpp"

class Add : public Action {
public:
    void execute() override;
};

#endif /* add_hpp */
