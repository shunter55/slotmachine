//
//  Symbol.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#ifndef Symbol_hpp
#define Symbol_hpp

#include <stdio.h>
#include "Value.hpp"

class Symbol {
public:
    Symbol(int number, int numValues, Value *values[5]);
    
    int number;
    std::string image;
    int numValues;
    Value *values[5];
    
    int getValue(int occurances);
    int getOccurances(int value);
    int minOccurance();
    int maxOccurancesWithValueBelow(int maxValue);
    int minOccurancesWithValueAbove(int minValue);
};

#endif /* Symbol_hpp */
