//
//  base64.hpp
//  qs
//
//  Created by Peter Xu on 5/19/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//
//  Credit: http://www.adp-gmbh.ch/cpp/common/base64.html
//

#ifndef base64_hpp
#define base64_hpp

#include <stdio.h>

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

#endif /* base64_hpp */
