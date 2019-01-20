/*
 * Long.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "base/Long.h"
#include "base/Character.h"
#include "base/UnicodeString.h"
#include "base/exceptions.h"

namespace alinous {

Long::Long() {
}

Long::~Long() {
}

int64_t Long::parseLong(UnicodeString* string) {
	return parseLong(string, 10);
}

int64_t Long::parseLong(UnicodeString* string, int radix){
	int length = string->length(), i = 0;
	bool negative = string->charAt(i) == '-';

	return parse(string, i, radix, negative);
}

int64_t Long::parse(UnicodeString* string, int offset, int radix, bool negative) {
    int64_t result = 0;
    int64_t length = string->length();
    while (offset < length) {
        int digit = Character::digit(string->charAt(offset++), radix);
        if (digit == -1) {
            throw new NumberFormatException(__FILE__, __LINE__);
        }
        int64_t next = result * radix - digit;
        if (next > result) {
            throw new NumberFormatException(__FILE__, __LINE__);
        }
        result = next;
    }
    if (!negative) {
        result = -result;
        if (result < 0) {
            throw new NumberFormatException(__FILE__, __LINE__);
        }
    }
    return result;
}

int Long::numberOfLeadingZeros(int64_t lng) {
    lng |= lng >> 1;
    lng |= lng >> 2;
    lng |= lng >> 4;
    lng |= lng >> 8;
    lng |= lng >> 16;
    lng |= lng >> 32;
    return bitCount(~lng);
}

int Long::bitCount(int64_t lng) {
    lng = (lng & 0x5555555555555555L) + ((lng >> 1) & 0x5555555555555555L);
    lng = (lng & 0x3333333333333333L) + ((lng >> 2) & 0x3333333333333333L);
    // adjust for 64-bit integer
    int i = (int) ((((uint64_t)lng) >> 32) + lng);
    i = (i & 0x0F0F0F0F) + ((i >> 4) & 0x0F0F0F0F);
    i = (i & 0x00FF00FF) + ((i >> 8) & 0x00FF00FF);
    i = (i & 0x0000FFFF) + ((i >> 16) & 0x0000FFFF);
    return i;
}

} /* namespace alinous */
