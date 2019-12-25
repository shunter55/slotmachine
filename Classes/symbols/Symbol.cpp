//
//  Symbol.cpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#include <stdio.h>
#include "Symbol.hpp"
#include "Symbols.hpp"

using namespace std;

Symbol::Symbol(int number, int numValues, Value *values[5]) {
    this->number = number;
    this->numValues = numValues;
    stringstream imageStream;
    imageStream << "symbols/" << Symbols::symbolPath(number);
    this->image = imageStream.str();
    std::memcpy(this->values, values, 5 * sizeof(Value *));
}

/**
 * @return the monetary value of the Symbol for the given occurances. -1 for error.
 */
int Symbol::getValue(int occurances) {
    for (int i = 0; i < numValues; i++) {
        Value *val = values[i];
        if (occurances < val->occurrence) {
            return 0;
        } else if (occurances == val->occurrence) {
            return val->value;
        }
    }
    return -1;
}

/**
 * @return the number of occurances given a value. -1 for error.
 */
int Symbol::getOccurances(int value) {
    for (int i = 0; i < numValues; i++) {
        if (value == values[i]->value) {
            return values[i]->occurrence;
        }
    }
    return -1;
}

int Symbol::minOccurance() {
    return values[0]->occurrence;
}

int Symbol::maxOccurancesWithValueBelow(int maxValue) {
    int occ = 5;
    for (int i = numValues - 1; i >= 0 && values[i]->value > maxValue; i--) {
        occ--;
    }
    return occ;
}

int Symbol::minOccurancesWithValueAbove(int minValue) {
    int occ = minOccurance();
    for (int i = 0; i < numValues && values[i]->value < minValue; i++) {
        occ++;
    }
    return occ;
}
