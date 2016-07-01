//
//  Tokenizer.hpp
//  qs
//
//  Created by Peter Xu on 6/28/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef tokenizer_hpp
#define tokenizer_hpp

#include <stdio.h>
#include <list>

#include "token.hpp"

using std::list;

namespace Tokenizer {
    
    list<Token *> tokenize(int rawc, const char * raw[]);
    
}

#endif /* tokenizer_hpp */
