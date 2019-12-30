//
//  Board.cpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//
#include <iostream>

#include "Board.hpp"
#include "Symbols.hpp"
#include "Symbol.hpp"
#include "Lines.hpp"
#include "Line.hpp"
#include "LineValue.hpp"
#include "Utils.hpp"


using namespace std;

Board::Board() {
    //randomize();
}

void Board::init(float wcp, float gwcp, Symbols *symbols, Lines *lines) {
    int calculateBoard = Utils::random(0, 99);
    if (calculateBoard < wcp * 100) {
        if (calculateBoard < gwcp * 100) {
            // Should win over $25.
            valueInRange(26, 1000, symbols, lines);
        } else {
            // Should win between $1 and $25.
            valueInRange(1, 25, symbols, lines);
        }
    } else {
        // Should lose.
        losingBoard(symbols, lines);
    }
}

void Board::init() {
    // Initialize board to -1.
    for (int y = 0; y < Board::height; y++) {
        for (int x = 0; x < Board::width; x++) {
            board[x][y] = -1;
        }
    }
}

void Board::losingBoard(Symbols *symbols, Lines *lines) {
    init();
    
    fillBoard(symbols, lines);
}

void Board::valueInRange(int low, int high, Symbols *symbols, Lines *lines) {    
    init();
    
    int numWinningLines = Utils::random(1, 4);
    Line *winningLines[4];
    Symbol *winningSymbols[4];
    for (int i = 0; i < numWinningLines; i++) {
        // Pick Random Lines.
        winningLines[i] = lines->lines[Utils::random(0, Lines::TOTAL_LINES - 1)];
        // Pick Random Symbols.
        winningSymbols[i] = symbols->symbols[Utils::random(0, Symbols::NUM_SYMBOLS - 1)];
    }
    
    for (int i = 0; i < numWinningLines; i++) {
        Line *winningLine = winningLines[i];
        Symbol *symbol = winningSymbols[i];
        
        // Find range of occurances that fit bounds.
        int maxOcc = symbol->maxOccurancesWithValueBelow(high);
        int minOcc = symbol->minOccurancesWithValueAbove(low);
        if (maxOcc < minOcc) {
            // Symbol cannot make the requested range. TODO: Don't just randomly regenerate.
            std::cout << "WARN: symbol: " << symbol->number << " - Make sure all symbols can make the range(" << low << ", " << high << ")" << std::endl;
            valueInRange(low, high, symbols, lines);
            return;
        }
        int occ = Utils::random(minOcc, maxOcc);
        for (int x = 0; x < occ; x++) {
            // Lines could cross and overwrite eachother, but last line will have winning value.
            board[x][winningLine->get(x)] = symbol->number;
        }
    }
    
    fillBoard(symbols, lines);
}

void Board::fillBoard(Symbols *symbols, Lines *lines) {
    // Randomize 1st row Symbols if not defined.
    for (int y = 0; y < Board::height; y++) {
        if (board[0][y] == -1) {
            board[0][y] = Utils::random(0, Symbols::NUM_SYMBOLS - 1);
        }
    }
    
    // Get possible symbols.
    int possibleSymbols[Symbols::NUM_SYMBOLS];
    int idx = 0;
    for (int num = 0; num < Symbols::NUM_SYMBOLS; num++) {
        bool inFirstRow = false;
        for (int y = 0; y < Board::height; y++) {
            if (board[0][y] == num) {
                inFirstRow = true;
            }
        }
        if (!inFirstRow) {
            possibleSymbols[idx++] = num;
        }
    }
    
    // Randomize the rest of the board with Symbols that arnt in the 1st row.
    for (int y = 0; y < Board::height; y++) {
        for (int x = 0; x < Board::width; x++) {
            if (board[x][y] == -1) {
                board[x][y] = possibleSymbols[Utils::random(0, idx - 1)];
            }
        }
    }
}

void Board::randomize() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            board[x][y] = Utils::random(0, Symbols::NUM_SYMBOLS - 1);
        }
    }
}

Symbol *Board::get(Symbols *symbols, int x, int y) {
    return symbols->symbols[board[x][y]];
}

/**
 * @return The monetary value of the line. 0 if the line is losing. > 0 if winning.
 */
int Board::checkLine(Symbols *symbols, Line *line) {
    Symbol *symbol = get(symbols, 0, line->get(0));
    int numOccurancesOnLine = 1;
    
    for (int x = 1; x < Board::width && (symbol->number == get(symbols, x, line->get(x))->number); x++) {
        numOccurancesOnLine++;
    }
    
    return symbol->getValue(numOccurancesOnLine);
}

vector<LineValue *> *Board::checkLines(Symbols *symbols, Lines *lines) {
    vector<LineValue *> *matchedLines = new vector<LineValue *>();
    
    for (int i = 0; i < Lines::TOTAL_LINES; i++) {
        Line *line = lines->lines[i];
        int value = checkLine(symbols, line);
        if (value > 0) {
            matchedLines->push_back(new LineValue(line, value));
        }
    }
    return matchedLines;
}

LineValue *Board::score(Symbols *symbols, Lines *lines) {
    vector<LineValue *> *lineValues = checkLines(symbols, lines);
    
    LineValue *maxLineValue = nullptr;
    for (int i = 0; i < lineValues->size(); i++) {
        LineValue *lineValue = lineValues->at(i);
        if (maxLineValue == nullptr || maxLineValue->value < lineValue->value) {
            maxLineValue = lineValue;
        }
    }
    // TODO: Cleanup memory.
    return maxLineValue;
}

void Board::demoteLine(LineValue *lineValue, int minValue, int maxValue, Symbols *symbols) {
    Symbol *symbol = get(symbols, 0, lineValue->line->get(0));
    int occurances = symbol->getOccurances(lineValue->value);
    
    if (occurances > symbol->minOccurance()) {
        // Can we reduce number to get below maxValue and above minValue?
        while (occurances > symbol->minOccurance() && symbol->getValue(occurances) > maxValue) {
            occurances--;
        }
        if (symbol->getValue(occurances) >= minValue && symbol->getValue(occurances) <= maxValue) {
            // Set Symbol occurances.
            return;
        }
    }
    
    // Use a different Symbol.
    
}

string Board::toString() {
    std::stringstream str;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            str << board[x][y];
        }
        str << endl;
    }
    
    return str.str();
}
