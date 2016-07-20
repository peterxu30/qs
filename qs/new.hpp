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
#include <ios>
#include <unordered_map>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <Poco/Net/MailMessage.h>

#include "action.hpp"
#include "email_manager.hpp"
#include "log_manager.hpp"

class New : public Action {
public:
    void execute() override;
private:
    string promptMsg();
};

#endif /* new_hpp */
