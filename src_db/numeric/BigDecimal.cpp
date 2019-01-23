/*
 * BigDecimal.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "numeric/BigDecimal.h"
#include "numeric/BigInteger.h"
#include "numeric/Multiplication.h"

#include "base/Integer.h"
#include "base/Long.h"
#include "base/UnicodeString.h"
#include "base/exceptions.h"
#include "base/StackRelease.h"

namespace alinous {

BigDecimal::BigDecimal(UnicodeString* val) {
	this->intVal = nullptr;

	int len = val->length();
	int16_t* in = new int16_t[len]{};
	StackArrayRelease<int16_t> __st_in(in);

	for(int i = 0; i != len; ++i){
		in[i] = val->charAt(i);
	}

	__BigDecimal(in, 0, len);
}

BigDecimal::~BigDecimal() {
	if(this->intVal){
		delete this->intVal;
	}

}

void BigDecimal::__BigDecimal(int16_t* in, int offset, int len) {
	StackMultipleRelease<UnicodeString> __st_unicode;

	int begin = offset;
	int last = offset + (len - 1);
	UnicodeString* unscaledBuffer; // buffer for unscaled value

    unscaledBuffer = new UnicodeString(L""); __st_unicode.add(unscaledBuffer);
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
        UnicodeString* scaleString = UnicodeString::valueOf(in, begin, last + 1 - begin);
        StackRelease<UnicodeString> __st_scaleString(scaleString);
        // Checking if the scale is defined
        int64_t newScale = (int64_t)scale - Integer::parseInt(scaleString);
        scale = (int)newScale;
      //  if (newScale != scale) {
      //      throw new NumberFormatException(__FILE__, __LINE__);
      //  }
    }

    // Parsing the unscaled value

    if (bufLength < 19) {
        smallValue = Long::parseLong(unscaledBuffer);
        bitLength = __bitLength(smallValue);
    } else {
        setUnscaledValue(BigInteger(unscaledBuffer));
    }
    precision = unscaledBuffer->length() - counter;
    if (unscaledBuffer->charAt(0) == L'-') {
        precision --;
    }

}

int BigDecimal::__bitLength(int64_t smallValue) {
    if(smallValue < 0) {
        smallValue = ~smallValue;
    }
    return 64 - Long::numberOfLeadingZeros(smallValue);
}

void BigDecimal::setUnscaledValue(const BigInteger& unscaledValue) {
    this->intVal = new BigInteger(unscaledValue);
    this->bitLength = unscaledValue.bitLength();
    if(this->bitLength < 64) {
        this->smallValue = unscaledValue.longValue();
    }
}

BigInteger BigDecimal::getUnscaledValue() {
	if(intVal == nullptr) {
		intVal = new BigInteger(BigInteger::valueOf(smallValue));
	}
    return *intVal;
}

bool BigDecimal::isZero() const {
	return this->bitLength == 0 && this->smallValue != -1;
}

int BigDecimal::aproxPrecision() const {
    return (this->precision > 0) ? this->precision
            : ((int) ((this->bitLength - 1) * LOG10_2)) + 1;
}

int64_t alinous::BigDecimal::longValue() {
    return ((scale <= -64) || (scale > aproxPrecision())
    ? 0L
            : toBigInteger().longValue());
}

BigInteger BigDecimal::toBigInteger() {
    if ((scale == 0) || (isZero())) {
        return getUnscaledValue();
    } else if (scale < 0) {
        return getUnscaledValue().multiply(Multiplication::powerOf10(-(int64_t)scale));
    } else {// (scale > 0)
    	BigInteger tmp = getUnscaledValue();
        return tmp.divide(Multiplication::powerOf10(scale));
    }
}

} /* namespace alinous */
