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

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <Poco/Net/MailMessage.h>

#include "action.hpp"
#include "email_manager.hpp"

class New : public Action {
public:
    void execute() override;
private:
    void interactiveNewMsg();
    void interactiveNewFile();
    void interactiveNewFull();
};

#endif /* new_hpp */
