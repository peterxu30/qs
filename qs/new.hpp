//
//  new.hpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef new_hpp
#define new_hpp

#include <stdio.h>

#include "action.hpp"

class New : public Action {
public:
    void execute() override;
};

#endif /* new_hpp */
