/*
 * BigInteger.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "numeric/BigInteger.h"
#include "numeric/BitLevel.h"
#include "numeric/Conversion.h"
#include "numeric/Division.h"
#include "numeric/Multiplication.h"
#include "numeric/Elementary.h"
#include "numeric/exceptions.h"

#include "base/UnicodeString.h"
#include "base/Integer.h"

#include "base/StackRelease.h"
#include "base/ArrayList.h"

namespace alinous {

const BigInteger* BigInteger::SMALL_VALUE = BigInteger::__SMALL_VALUES();

BigInteger* BigInteger::__SMALL_VALUES() {
	static BigInteger SMALL_VALUES[11]{ BigInteger(0, 0), BigInteger(1, 1), BigInteger(1, 2),
        BigInteger(1, 3), BigInteger(1, 4), BigInteger(1, 5),
        BigInteger(1, 6), BigInteger(1, 7), BigInteger(1, 8),
        BigInteger(1, 9), BigInteger(1, 10) };

	return SMALL_VALUES;
}

const BigInteger BigInteger::ZERO(0, 0);
const BigInteger BigInteger::ONE(1, 1);
BigInteger BigInteger::TEN(1, 10);

BigInteger** BigInteger::TWO_POWS = initTwoPows();
BigInteger** BigInteger::initTwoPows() {
	static bool init = false;
	static ArrayList<BigInteger> __TWO_POWS(32);

	if(!init){
		__TWO_POWS.setDeleteOnExit();

        for(int i = 0; i < 32; i++) {
            TWO_POWS[i] = BigInteger::valueOf(1L<<i);
        }

		init = true;
	}

	return __TWO_POWS.getRoot();
}

BigInteger::BigInteger(const BigInteger& inst) {
	this->firstNonzeroDigit = inst.firstNonzeroDigit;
	this->sign = inst.sign;
	this->numberLength = inst.numberLength;
	this->digits = new int[this->numberLength] {};

	for(int i = 0; i != this->numberLength; ++i){
		this->digits[i] = inst.digits[i];
	}

}

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

BigInteger::BigInteger(int sign, int numberLength, int* digits) {
	this->firstNonzeroDigit = -2;

    this->sign = sign;
    this->numberLength = numberLength;
    this->digits = digits;
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
    	UnicodeString* subStr = val->substring(substrStart, substrEnd);
    	StackRelease<UnicodeString> __st_subStr(subStr);

        int bigRadixDigit = Integer::parseInt(subStr, radix);
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

BigInteger* BigInteger::multiply(const BigInteger* val) const {
    // This let us to throw NullPointerException when val == null
    if (val->sign == 0) {
        return new BigInteger(0, 0);
    }
    if (sign == 0) {
        return new BigInteger(0, 0);
    }

    return Multiplication::multiply(this, val);
}

BigInteger* BigInteger::shiftRight(int n) const {
    if ((n == 0) || (sign == 0)) {
        return new BigInteger(*this);
    }
    return ((n > 0) ? BitLevel::shiftRight(this, n) : BitLevel::shiftLeft(this, -n));
}

BigInteger* BigInteger::shiftLeft(int n) {
    if ((n == 0) || (sign == 0)) {
        return this;
    }
    return ((n > 0) ? BitLevel::shiftLeft(this, n) : BitLevel::shiftRight(this, -n));
}

BigInteger* BigInteger::subtract(BigInteger* val) const {
	return Elementary::subtract(this, val);
}

BigInteger* BigInteger::add(BigInteger* val) {
	return Elementary::add(this, val);
}

BigInteger* BigInteger::divide(BigInteger* divisor) {
    if (divisor->sign == 0) {
        // math.17=BigInteger divide by zero
        throw new ArithmeticException(L"BigInteger divide by zero", __FILE__, __LINE__); //$NON-NLS-1$
    }
    int divisorSign = divisor->sign;
    if (divisor->isOne()) {
        return ((divisor->sign > 0) ? new BigInteger(*this) : this->negate());
    }
    int thisSign = sign;
    int thisLen = numberLength;
    int divisorLen = divisor->numberLength;
    if (thisLen + divisorLen == 2) {
        long val = (digits[0] & 0xFFFFFFFFL)
                / (divisor->digits[0] & 0xFFFFFFFFL);
        if (thisSign != divisorSign) {
            val = -val;
        }
        return valueOf(val);
    }
    int cmp = ((thisLen != divisorLen) ? ((thisLen > divisorLen) ? 1 : -1)
            : Elementary::compareArrays(digits, divisor->digits, thisLen));
    if (cmp == EQUALS) {
        return ((thisSign == divisorSign) ? new BigInteger(1, 1) : new BigInteger(1, -1));
        //return ((thisSign == divisorSign) ? ONE : MINUS_ONE);
    }
    if (cmp == LESS) {
        return new BigInteger(0, 0); // ZERO;
    }
    int resLength = thisLen - divisorLen + 1;
    int* resDigits = new int[resLength];
    int resSign = ((thisSign == divisorSign) ? 1 : -1);
    if (divisorLen == 1) {
        Division::divideArrayByInt(resDigits, digits, thisLen,
                divisor->digits[0]);
    } else {
        delete [] Division::divide(resDigits, resLength, digits, thisLen,
                divisor->digits, divisorLen);
    }
    BigInteger* result = new BigInteger(resSign, resLength, resDigits);
    result->cutOffLeadingZeroes();
    return result;
}

bool BigInteger::isOne() {
	return ((numberLength == 1) && (digits[0] == 1));
}

BigInteger* BigInteger::pow(int exp) {
    if (exp < 0) {
        // math.16=Negative exponent
        throw new ArithmeticException(L"Negative exponent", __FILE__, __LINE__); //$NON-NLS-1$
    }
    if (exp == 0) {
        return new BigInteger(1, 1); // ONE;
    } else if (exp == 1 || equals(&ONE) || equals(&ZERO)) {
        return new BigInteger(*this);
    }

    // if even take out 2^x factor which we can
    // calculate by shifting.
    if (!testBit(0)) {
        int x = 1;
        while (!testBit(x)) {
            x++;
        }
        return getPowerOfTwo(x*exp)->multiply(this->shiftRight(x)->pow(exp));
    }
    return Multiplication::pow(this, exp);
}

bool BigInteger::equals(const BigInteger* x1) const {
    return sign == x1->sign && numberLength == x1->numberLength
            && equalsArrays(x1->digits);
}

bool BigInteger::equalsArrays(const int* b) const {
    int i;
    for (i = numberLength - 1; (i >= 0) && (digits[i] == b[i]); i--) {
        // Empty
    }
    return i < 0;
}

bool BigInteger::testBit(int n) {
    if (n == 0) {
        return ((digits[0] & 1) != 0);
    }
    if (n < 0) {
        // math.15=Negative bit address
        throw new ArithmeticException(L"Negative bit address", __FILE__, __LINE__); //$NON-NLS-1$
    }
    int intCount = n >> 5;
    if (intCount >= numberLength) {
        return (sign < 0);
    }
    int digit = digits[intCount];
    n = (1 << (n & 31)); // int with 1 set to the needed position
    if (sign < 0) {
        int firstNonZeroDigit = getFirstNonzeroDigit();
        if (intCount < firstNonZeroDigit) {
            return false;
        } else if (firstNonZeroDigit == intCount) {
            digit = -digit;
        } else {
            digit = ~digit;
        }
    }
    return ((digit & n) != 0);
}

BigInteger* BigInteger::getPowerOfTwo(int exp) {
    if(exp < 32){ // TWO_POWS.length) {
        return new BigInteger(*TWO_POWS[exp]);
    }
    int intCount = exp >> 5;
    int bitN = exp & 31;
    int* resDigits = new int[intCount+1];
    resDigits[intCount] = 1 << bitN;

    return new BigInteger(1, intCount+1, resDigits);
}

void BigInteger::cutOffLeadingZeroes() {
    while ((numberLength > 0) && (digits[--numberLength] == 0)) {
        // Empty
    }
    if (digits[numberLength++] == 0) {
        sign = 0;
    }
}

BigInteger* BigInteger::negate() const {
    return ((sign == 0) ? new BigInteger(*this)
            : new BigInteger(-sign, numberLength, digits));
}

BigInteger* BigInteger::valueOf(int64_t val) {
    if (val < 0) {
        if (val != -1) {
            return new BigInteger(-1, -val);
        }
        return new BigInteger(-1, -1);
    } else if (val <= 10) {
        return new BigInteger(BigInteger::SMALL_VALUE[(int) val]);
    } else {// (val > 10)
        return new BigInteger(1, val);
    }
}

} /* namespace alinous */
