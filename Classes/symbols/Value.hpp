//
//  Value.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#ifndef Value_hpp
#define Value_hpp

#include <stdio.h>

class Value {
public:
    Value(int occurrence, int value) {
        this->occurrence = occurrence;
        this->value = value;
    }
    
    int occurrence;
    int value;
};

#endif /* Value_hpp */
