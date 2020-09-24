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
#include "base/StackRelease.h"

namespace alinous {

Long::Long() {
}

Long::~Long() {
}

int64_t Long::parseLong(const UnicodeString* string) {
	return parseLong(string, 10);
}

int64_t Long::parseLong(const UnicodeString* string, int radix){
	bool negative = string->charAt(0) == L'-';
	int offset = 0;
	if(negative){
		offset++;
	}

	return parse(string, offset, radix, negative);
}

int64_t Long::parse(const UnicodeString* string, int offset, int radix, bool negative) {
    int64_t result = 0;
    int64_t length = string->length();
    while (offset < length) {
        int digit = Character::digit(string->charAt(offset++), radix);
        if (digit == -1) {
            throw new NumberFormatException(__FILE__, __LINE__);
        }
        int64_t next = result * radix - digit;
        result = next;
    }
    if (!negative) {
        result = -result;
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
    lng = (lng & 0x5555555555555555LL) + ((lng >> 1) & 0x5555555555555555LL);
    lng = (lng & 0x3333333333333333LL) + ((lng >> 2) & 0x3333333333333333LL);
    // adjust for 64-bit integer
    int i = (int) ((((uint64_t)lng) >> 32) + lng);
    i = (i & 0x0F0F0F0F) + ((i >> 4) & 0x0F0F0F0F);
    i = (i & 0x00FF00FF) + ((i >> 8) & 0x00FF00FF);
    i = (i & 0x0000FFFF) + ((i >> 16) & 0x0000FFFF);
    return i;
}

UnicodeString* Long::toString(int64_t l, int radix) {
    if (radix < Character::MIN_RADIX || radix > Character::MAX_RADIX) {
        radix = 10;
    }
    if (l == 0) {
        return new UnicodeString(L"0"); //$NON-NLS-1$
    }

    int count = 2;
    long j = l;
    bool negative = l < 0;
    if (!negative) {
        count = 1;
        j = -l;
    }
    while ((l /= radix) != 0) {
        count++;
    }

    wchar_t* buffer = new wchar_t[count + 1]{};
    StackArrayRelease<wchar_t> __st_buffer(buffer);

    do {
        int ch = 0 - (int) (j % radix);
        if (ch > 9) {
            ch = ch - 10 + L'a';
        } else {
            ch += L'0';
        }
        buffer[--count] = (wchar_t) ch;
    } while ((j /= radix) != 0);
    if (negative) {
        buffer[0] = L'-';
    }
    //return new UnicodeString(0, buffer.length, buffer);
    return new UnicodeString(buffer);
}

} /* namespace alinous */
