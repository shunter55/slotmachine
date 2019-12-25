//
//  Lines.cpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#include "Line.hpp"
#include "Lines.hpp"

using namespace std;

Lines::Lines() {
    for (int i = 0; i < 25; i++) {
        lines[i] = new Line(i, lineDefs[i]);
    }
};

const string Lines::lineDefs[] = {
    "ooooo\n"
    "xxxxx\n"
    "ooooo\n",
    
    "xxxxx\n"
    "ooooo\n"
    "ooooo\n",
    
    "ooooo\n"
    "ooooo\n"
    "xxxxx\n",
    
    "xooox\n"
    "oxoxo\n"
    "ooxoo\n",
    
    "ooxoo\n"
    "oxoxo\n"
    "xooox\n",
    
    "oxxxo\n"
    "xooox\n"
    "ooooo\n",
    
    "ooooo\n"
    "xooox\n"
    "oxxxo\n",
    
    "xxooo\n"
    "ooxoo\n"
    "oooxx\n",
    
    "oooxx\n"
    "ooxoo\n"
    "xxooo\n",
    
    "oooxo\n"
    "xoxox\n"
    "oxooo\n",
    
    "oxooo\n"
    "xoxox\n"
    "oooxo\n",
    
    "xooox\n"
    "oxxxo\n"
    "ooooo\n",
    
    "ooooo\n"
    "oxxxo\n"
    "xooox\n",
    
    "xoxox\n"
    "oxoxo\n"
    "ooooo\n",
    
    "ooooo\n"
    "oxoxo\n"
    "xoxox\n",
    
    "ooxoo\n"
    "xxoxx\n"
    "ooooo\n",
    
    "ooooo\n"
    "xxoxx\n"
    "ooxoo\n",
    
    "xxoxx\n"
    "ooooo\n"
    "ooxoo\n",
    
    "ooxoo\n"
    "ooooo\n"
    "xxoxx\n",
    
    "xooox\n"
    "ooooo\n"
    "oxxxo\n",
    
    "oxxxo\n"
    "ooooo\n"
    "xooox\n",
    
    "ooxoo\n"
    "xooox\n"
    "oxoxo\n",
    
    "oxoxo\n"
    "xooox\n"
    "ooxoo\n",
    
    "xoxox\n"
    "ooooo\n"
    "oxoxo\n",
    
    "oxoxo\n"
    "ooooo\n"
    "xoxox\n"
};
