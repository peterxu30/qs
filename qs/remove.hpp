//
//  remove.hpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef remove_hpp
#define remove_hpp

#include <stdio.h>

#include "accounts_manager.hpp"
#include "action.hpp"
#include "email_manager.hpp"

class Remove : public Action {
public:
    void execute() override;
};

#endif /* remove_hpp */
