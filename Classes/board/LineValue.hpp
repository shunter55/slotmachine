//
//  LineValue.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/24/19.
//

#ifndef LineValue_hpp
#define LineValue_hpp

#include <stdio.h>
#include "Line.hpp"

class LineValue {
public:
    LineValue(Line *line, int value);
    Line *line;
    int value;
};

#endif /* LineValue_hpp */
