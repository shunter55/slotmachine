//
//  line.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#ifndef line_hpp
#define line_hpp

#include <stdio.h>

class Line {
public:
    Line(int number, std::string str);
    int number;
    std::string image;
    int get(int x);
    std::string toString();
private:
    bool board[5][3];
};

#endif /* line_hpp */
