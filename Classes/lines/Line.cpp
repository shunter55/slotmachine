//
//  line.cpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#include <iostream>
#include "Line.hpp"
#include "Board.hpp"

using namespace std;

Line::Line(int number, string str) {
    this->number = number;
    
    stringstream imageStream;
    imageStream << "lines/line" << number + 1 << ".png";
    this->image = imageStream.str();
    
    stringstream ss(str);
    string line;
    
    int y = 0;
    while (getline(ss, line)) {
        for (int x = 0; x < 5; x++) {
            board[x][y] = line[x] == 'x';
        }
        y++;
    }
}

/**
 * @return the y value of the Line given an x. -1 if no value found.
 */
int Line::get(int x) {
    for (int y = 0; y < Board::height; y++) {
        if (board[x][y]) {
            return y;
        }
    }
    return -1;
}

string Line::toString() {
    std::stringstream str;
    
    for (int y = 0; y < Board::height; y++) {
        for (int x = 0; x < Board::width; x++) {
            str << board[x][y];
        }
        str << endl;
    }
    
    return str.str();
}

