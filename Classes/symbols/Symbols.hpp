//
//  Symbols.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#ifndef Symbols_hpp
#define Symbols_hpp

#include <stdio.h>
#include "Value.hpp"
#include "Symbol.hpp"

class Symbols {
public:
    Symbols();
    
    static const int NUM_SYMBOLS = 10;
    static std::string symbolPath(int s);
    Symbol *symbols[NUM_SYMBOLS];

private:
    static const std::string symbolDefs[NUM_SYMBOLS];
};

#endif /* Symbols_hpp */
