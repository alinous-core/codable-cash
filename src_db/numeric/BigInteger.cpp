/*
 * BigInteger.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "numeric/BigInteger.h"
#include "numeric/BitLevel.h"
#include "numeric/Conversion.h"
#include "numeric/Multiplication.h"
#include "numeric/Elementary.h"

#include "base/UnicodeString.h"
#include "base/Integer.h"

namespace alinous {

BigInteger::BigInteger(int sign, int value) {
	this->firstNonzeroDigit = -2;
    this->sign = sign;
    this->numberLength = 1;
    this->digits = new int[1] { value };

}

BigInteger::BigInteger(UnicodeString* val, int radix) {
	this->firstNonzeroDigit = -2;

	setFromString(this, val, radix);
}

BigInteger::BigInteger(UnicodeString* val) {
	this->firstNonzeroDigit = -2;

	setFromString(this, val, 10);
}

void BigInteger::setFromString(BigInteger* bi, UnicodeString* val, int radix) {
    int sign;
    int* digits;
    int numberLength;
    int stringLength = val->length();
    int startChar;
    int endChar = stringLength;

    if (val->charAt(0) == L'-') {
        sign = -1;
        startChar = 1;
        stringLength--;
    } else {
        sign = 1;
        startChar = 0;
    }

    int charsPerInt = Conversion::digitFitInInt[radix];
    int bigRadixDigitsLength = stringLength / charsPerInt;
    int topChars = stringLength % charsPerInt;

    if (topChars != 0) {
        bigRadixDigitsLength++;
    }
    digits = new int[bigRadixDigitsLength];
    // Get the maximal power of radix that fits in int
    int bigRadix = Conversion::bigRadices[radix - 2];
    // Parse an input string and accumulate the BigInteger's magnitude
    int digitIndex = 0; // index of digits array
    int substrEnd = startChar + ((topChars == 0) ? charsPerInt : topChars);

    for (int substrStart = startChar; substrStart < endChar; substrStart = substrEnd, substrEnd = substrStart
            + charsPerInt) {
        int bigRadixDigit = Integer::parseInt(val->substring(substrStart, substrEnd), radix);
        int newDigit = Multiplication::multiplyByInt(digits, digitIndex, bigRadix);
        newDigit += Elementary::inplaceAdd(digits, digitIndex, bigRadixDigit);
        digits[digitIndex++] = newDigit;
    }
    numberLength = digitIndex;
    bi->sign = sign;
    bi->numberLength = numberLength;
    bi->digits = digits;
    bi->cutOffLeadingZeroes();
}


BigInteger::~BigInteger() {
	if(this->digits){
		delete [] this->digits;
	}
}

int BigInteger::bitLength() {
	return BitLevel::bitLength(this);
}

int BigInteger::getFirstNonzeroDigit() {
    if (firstNonzeroDigit == -2) {
        int i;
        if (this->sign == 0) {
            i = -1;
        } else {
            for (i = 0; digits[i] == 0; i++) {
                // Empty
            }
        }
        firstNonzeroDigit = i;
    }
    return firstNonzeroDigit;
}

int64_t BigInteger::longValue() {
	int64_t value = (numberLength > 1) ? (((int64_t) digits[1]) << 32)
            | (digits[0] & 0xFFFFFFFFL) : (digits[0] & 0xFFFFFFFFL);
    return (sign * value);
}

void BigInteger::cutOffLeadingZeroes() {
    while ((numberLength > 0) && (digits[--numberLength] == 0)) {
        // Empty
    }
    if (digits[numberLength++] == 0) {
        sign = 0;
    }
}

} /* namespace alinous */

