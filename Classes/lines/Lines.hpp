//
//  Lines.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#ifndef Lines_hpp
#define Lines_hpp

#include <stdio.h>
#include "Line.hpp"

class Lines {
public:
    Lines();
    
    static const int TOTAL_LINES = 25;
    static const std::string lineDefs[];
    Line *lines[25];
};

#endif /* Lines_hpp */
