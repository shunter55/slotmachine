//
//  LineValue.cpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/24/19.
//

#include "LineValue.hpp"
#include "Line.hpp"

LineValue::LineValue(Line *line, int value) {
    this->line = line;
    this->value = value;
}
