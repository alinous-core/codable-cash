/*
 * BitLevel.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "numeric/BitLevel.h"
#include "numeric/BigInteger.h"
#include "base/Integer.h"
#include "osenv/memory.h"

namespace alinous {

BitLevel::BitLevel() {
}

BitLevel::~BitLevel() {
}

int BitLevel::bitLength(const BigInteger& val) {
    if (val.sign == 0) {
        return 0;
    }
    int bLength = (val.numberLength << 5);
    int highDigit = val.digits[val.numberLength - 1];

    if (val.sign < 0) {
        int i = val.getFirstNonzeroDigit();
        // We reduce the problem to the positive case.
        if (i == val.numberLength - 1) {
            highDigit--;
        }
    }
    // Subtracting all sign bits
    bLength -= Integer::numberOfLeadingZeros(highDigit);
    return bLength;
}

BigInteger BitLevel::shiftLeft(const BigInteger* source, int count) {
    int intCount = count >> 5;
    count &= 31; // %= 32
    int resLength = source->numberLength + intCount
            + ( ( count == 0 ) ? 0 : 1 );
    int* resDigits = new int[resLength];

    shiftLeft(resDigits, resLength, source->digits, intCount, count);
    BigInteger result(source->sign, resLength, resDigits);
    result.cutOffLeadingZeroes();
    return result;
}

void BitLevel::shiftLeft(int* result, int result_len, int* source, int intCount, int count) {
    if (count == 0) {
        arraycopy(source, 0, result, intCount, result_len - intCount);
    } else {
        int rightShiftCount = 32 - count;

        result[result_len - 1] = 0;
        for (int i = result_len - 1; i > intCount; i--) {
            result[i] |=  ((unsigned int)source[i - intCount - 1]) >> rightShiftCount;
            result[i - 1] = source[i - intCount - 1] << count;
        }
    }

    for (int i = 0; i < intCount; i++) {
        result[i] = 0;
    }
}

BigInteger BitLevel::shiftRight(const BigInteger* source, int count) {
    int intCount = count >> 5; // count of integers
    count &= 31; // count of remaining bits
    if (intCount >= source->numberLength) {
        return ((source->sign < 0) ? BigInteger::ONE : BigInteger::ZERO);
    }

    int resLength = source->numberLength - intCount;
    int *resDigits = new int[resLength + 1];

    shiftRight(resDigits, resLength, source->digits, intCount, count);
    if (source->sign < 0) {
        // Checking if the dropped bits are zeros (the remainder equals to
        // 0)
        int i = 0;
        for (; (i < intCount) && (source->digits[i] == 0); i++) {
            ;
        }
        // If the remainder is not zero, add 1 to the result
        if ((i < intCount)
                || ((count > 0) && ((source->digits[i] << (32 - count)) != 0))) {
            for (i = 0; (i < resLength) && (resDigits[i] == -1); i++) {
                resDigits[i] = 0;
            }
            if (i == resLength) {
                resLength++;
            }
            resDigits[i]++;
        }
    }
    BigInteger result(source->sign, resLength, resDigits);
    result.cutOffLeadingZeroes();
    return result;
}

void BitLevel::arraycopy(int* src, int srcPos, int* dest, int destPos, int length) {
	for(int i = 0; i != length; ++i){
		dest[destPos + i] = src[srcPos + i];
	}
}

bool BitLevel::shiftRight(int* result, int resultLen, int* source, int intCount, int count) {
    int i;
    bool allZero = true;
    for (i = 0; i < intCount; i++)
        allZero &= source[i] == 0;
    if (count == 0) {
        arraycopy(source, intCount, result, 0, resultLen);
        i = resultLen;
    } else {
        int leftShiftCount = 32 - count;

        allZero &= ( source[i] << leftShiftCount ) == 0;
        for (i = 0; i < resultLen - 1; i++) {
            result[i] = ( ((unsigned int)source[i + intCount]) >> count )
            | ( source[i + intCount + 1] << leftShiftCount );
        }
        result[i] = ( ((unsigned int)source[i + intCount]) >> count );
        //i++;
    }

    return allZero;
}

void BitLevel::shiftLeftOneBit(int* result, int* source, int srcLen) {
    int carry = 0;
    for (int i = 0; i < srcLen; i++) {
        int val = source[i];
        result[i] = (val << 1) | carry;
        carry = ((unsigned int)val) >> 31;
    }
    if (carry != 0) {
        result[srcLen] = carry;
    }
}

} /* namespace alinous */
