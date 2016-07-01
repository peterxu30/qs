//
//  clear.hpp
//  qs
//
//  Created by Peter Xu on 6/30/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef clear_hpp
#define clear_hpp

#include <stdio.h>

#include "action.hpp"

class Clear : public Action {
public:
    void execute() override;
};

#endif /* clear_hpp */
