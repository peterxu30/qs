//
//  error_checking_macros.h
//  qs
//
//  Created by Peter Xu on 5/16/16.
//  Copyright © 2016 Peter Xu. All rights reserved.
//

#ifndef error_checking_macros_h
#define error_checking_macros_h

#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                << " line " << __LINE__ << ": " << message << std::endl; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)

#endif /* error_checking_macros_h */
