//
//  Symbols.cpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#include <iostream>

#include "Symbols.hpp"
#include "Symbol.hpp"
//#include "Symbol.cpp"
#include "Value.cpp"

using namespace std;

Symbols::Symbols() {
    for (int i = 0; i < 10; i++) {
        stringstream ss;
        string line;
        
        ss << symbolDefs[i];
        
        int number;
        Value *values[5];
        
        int lineNum = 0;
        int valueIdx = 0;
        while(getline(ss, line)) {
            if (lineNum == 0) {
                number = stoi(line);
            } else {
                stringstream tokenStream(line);
                string token;
                getline(tokenStream, token, ' ');
                int count = stoi(token);
                getline(tokenStream, token, ' ');
                int val = stoi(token);
                values[valueIdx++] = new Value(count, val);
            }
            lineNum++;
        }
                
        symbols[i] = new Symbol(i, number, values);
    }
}

const string Symbols::symbolDefs[10] = {
    "3\n"
    "3 2\n"
    "4 5\n"
    "5 15\n",
    
    "3\n"
    "3 5\n"
    "4 10\n"
    "5 25\n",
    
    "3\n"
    "3 10\n"
    "4 20\n"
    "5 75\n",
    
    "3\n"
    "3 15\n"
    "4 75\n"
    "5 150\n",
    
    "3\n"
    "3 20\n"
    "4 100\n"
    "5 200\n",
    
    "4\n"
    "2 5\n"
    "3 25\n"
    "4 125\n"
    "5 250\n",
    
    "4\n"
    "2 7\n"
    "3 30\n"
    "4 150\n"
    "5 350\n",
    
    "4\n"
    "2 10\n"
    "3 50\n"
    "4 200\n"
    "5 500\n",
    
    "4\n"
    "2 15\n"
    "3 45\n"
    "4 250\n"
    "5 750\n",
    
    "4\n"
    "2 20\n"
    "3 100\n"
    "4 500\n"
    "5 1000\n",
};

string Symbols::symbolPath(int s) {
    switch(s) {
        case 0: return "symbol01.png";
        case 1: return "symbol02.png";
        case 2: return "symbol03.png";
        case 3: return "symbol04.png";
        case 4: return "symbol05.png";
        case 5: return "symbol06.png";
        case 6: return "symbol07.png";
        case 7: return "symbol08.png";
        case 8: return "symbol09.png";
        case 9: return "symbol10.png";
        default: return "nullptr";
    }
};


