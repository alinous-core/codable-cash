/*
 * BigDecimal.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "numeric/BigDecimal.h"

#include "base/Integer.h"
#include "base/UnicodeString.h"
#include "base/exceptions.h"

namespace alinous {

BigDecimal::BigDecimal(UnicodeString* val) {
	int len = val->length();
	int16_t* in = new int16_t[len];
	for(int i = 0; i != len; ++i){
		in[i] = val->charAt(i);
	}

	__BigDecimal(in, 0, len);
}

BigDecimal::~BigDecimal() {

}

void BigDecimal::__BigDecimal(int16_t* in, int offset, int len) {
	int begin = offset;
	int last = offset + (len - 1);
	UnicodeString* scaleString = nullptr; // buffer for scale
	UnicodeString* unscaledBuffer; // buffer for unscaled value
    long newScale; // the new scale

    unscaledBuffer = new UnicodeString(L"");
    int bufLength = 0;

    if ((offset <= last) && (in[offset] == L'+')) {
        offset++;
        begin++;
    }

    int counter = 0;
    bool wasNonZero = false;

    // Accumulating all digits until a possible decimal point
    for (; (offset <= last) && (in[offset] != L'.') && (in[offset] != L'e') && (in[offset] != L'E'); offset++) {
        if (!wasNonZero) {
            if (in[offset] == L'0') {
                counter++;
            } else {
                wasNonZero = true;
            }
        }
    }

    unscaledBuffer->append(in, begin, offset - begin);
    bufLength += offset - begin;

    // A decimal point was found
    if ((offset <= last) && (in[offset] == L'.')) {
        offset++;
        // Accumulating all digits until a possible exponent
        begin = offset;
        for (; (offset <= last) && (in[offset] != L'e') && (in[offset] != L'E'); offset++) {
            if (!wasNonZero) {
                if (in[offset] == L'0') {
                    counter++;
                } else {
                    wasNonZero = true;
                }
            }
        }
        this->scale = offset - begin;
        bufLength += this->scale;
        unscaledBuffer->append(in, begin, scale);
    } else {
    	this->scale = 0;
    }

    // An exponent was found
    if ((offset <= last) && ((in[offset] == L'e') || (in[offset] == L'E'))) {
        offset++;
        // Checking for a possible sign of scale
        begin = offset;
        if ((offset <= last) && (in[offset] == L'+')) {
            offset++;
            if ((offset <= last) && (in[offset] != L'-')) {
                begin++;
            }
        }
        // Accumulating all remaining digits
        delete scaleString;
        scaleString = UnicodeString::valueOf(in, begin, last + 1 - begin);
        // Checking if the scale is defined
        newScale = (long)scale - Integer::parseInt(scaleString);
        scale = (int)newScale;
        if (newScale != scale) {
            throw new NumberFormatException(__FILE__, __LINE__);
        }
    }

    // Parsing the unscaled value
    /*
    if (bufLength < 19) {
        smallValue = Long::parseLong(unscaledBuffer);
        bitLength = bitLength(smallValue);
    } else {
        setUnscaledValue(new BigInteger(unscaledBuffer.toString()));
    }
    precision = unscaledBuffer.length() - counter;
    if (unscaledBuffer->charAt(0) == L'-') {
        precision --;
    }
    */
}

} /* namespace alinous */
