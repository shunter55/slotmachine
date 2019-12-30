//
//  Board.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>

#include "Lines.hpp"
#include "Line.hpp"
#include "LineValue.hpp"
#include "Symbols.hpp"
#include "Symbol.hpp"

class Board {
public:
    static const int width = 5;
    static const int height = 3;
    
    Board();
    void init();
    void init(float wcp, float gwcp, Symbols *symbols, Lines *lines);
    void losingBoard(Symbols *symbols, Lines *lines);
    Symbol *get(Symbols *symbols, int x, int y);
    void valueInRange(int low, int high, Symbols *symbols, Lines *lines);
    
    void randomize();
    std::vector<LineValue *> *checkLines(Symbols *symbols, Lines *lines);
    LineValue *score(Symbols *symbols, Lines *lines);
    std::string toString();
private:
    int board[5][3];
    
    int checkLine(Symbols *symbols, Line *line);
    void fillBoard(Symbols *symbols, Lines *lines);
};

#endif /* Board_hpp */
