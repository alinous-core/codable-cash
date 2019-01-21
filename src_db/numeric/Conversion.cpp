/*
 * Conversion.cpp
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#include "numeric/Conversion.h"
#include "numeric/BigInteger.h"
#include "numeric/Division.h"
#include "numeric/Math.h"

#include "base/UnicodeString.h"
#include "base/Character.h"
#include "base/Long.h"
#include "base/Integer.h"
#include "base/StackRelease.h"

namespace alinous {

constexpr int Conversion::digitFitInInt[];
constexpr int Conversion::bigRadices[];


UnicodeString* Conversion::bigInteger2String(const BigInteger& val, int radix) {
    int sign = val.sign;
    int numberLength = val.numberLength;
    int* digits = val.digits;

    if (sign == 0) {
        return new UnicodeString(L"0"); //$NON-NLS-1$
    }
    if (numberLength == 1) {
        int highDigit = digits[numberLength - 1];
        int64_t v = highDigit & 0xFFFFFFFFL;
        if (sign < 0) {
            v = -v;
        }
        return Long::toString(v, radix);
    }
    if ((radix == 10) || (radix < Character::MIN_RADIX) || (radix > Character::MAX_RADIX)) {
        return val.toString();
    }

    double bitsForRadixDigit = Math::log(radix) / Math::log(2);
    int resLengthInChars = (int) (val.abs().bitLength() / bitsForRadixDigit + ((sign < 0) ? 1
            : 0)) + 1;

    wchar_t* result = new wchar_t[resLengthInChars]{};
    int currentChar = resLengthInChars;
    int resDigit;
    if (radix != 16) {
        int* temp = new int[numberLength];
        StackArrayRelease<int> __st_temp(temp);

        arraycopy(digits, 0, temp, 0, numberLength);
        int tempLen = numberLength;
        int charsPerInt = digitFitInInt[radix];
        int i;
        // get the maximal power of radix that fits in int
        int bigRadix = bigRadices[radix - 2];
        while (true) {
            // divide the array of digits by bigRadix and convert remainders
            // to characters collecting them in the char array
            resDigit = Division::divideArrayByInt(temp, temp, tempLen,
                    bigRadix);
            int previous = currentChar;
            do {
                result[--currentChar] = Character::forDigit(
                        resDigit % radix, radix);
            } while (((resDigit /= radix) != 0) && (currentChar != 0));
            int delta = charsPerInt - previous + currentChar;
            for (i = 0; i < delta && currentChar > 0; i++) {
                result[--currentChar] = L'0';
            }
            for (i = tempLen - 1; (i > 0) && (temp[i] == 0); i--) {
                ;
            }
            tempLen = i + 1;
            if ((tempLen == 1) && (temp[0] == 0)) { // the quotient is 0
                break;
            }
        }
    } else {
        // radix == 16
        for (int i = 0; i < numberLength; i++) {
            for (int j = 0; (j < 8) && (currentChar > 0); j++) {
                resDigit = digits[i] >> (j << 2) & 0xf;
                result[--currentChar] = Character::forDigit(resDigit, 16);
            }
        }
    }
    while (result[currentChar] == L'0') {
        currentChar++;
    }
    if (sign == -1) {
        result[--currentChar] = L'-';
    }
    return new UnicodeString(result, currentChar, resLengthInChars - currentChar);
}

UnicodeString* Conversion::toDecimalScaledString(BigInteger val, int scale) {
    int sign = val.sign;
    int numberLength = val.numberLength;
    int* digits = val.digits;
    int resLengthInChars;
    int currentChar;

    if (sign == 0) {
        switch (scale) {
            case 0:
                return new UnicodeString(L"0"); //$NON-NLS-1$
            case 1:
                return new UnicodeString(L"0.0"); //$NON-NLS-1$
            case 2:
                return new UnicodeString(L"0.00"); //$NON-NLS-1$
            case 3:
                return new UnicodeString(L"0.000"); //$NON-NLS-1$
            case 4:
                return new UnicodeString(L"0.0000"); //$NON-NLS-1$
            case 5:
                return new UnicodeString(L"0.00000"); //$NON-NLS-1$
            case 6:
                return new UnicodeString(L"0.000000"); //$NON-NLS-1$
            default:
                UnicodeString* result1 = new UnicodeString(L"");
                if (scale < 0) {
                    result1->append(L"0E+"); //$NON-NLS-1$
                } else {
                    result1->append(L"0E"); //$NON-NLS-1$
                }
                result1->append(-scale);
                return result1;
        }
    }
    // one 32-bit unsigned value may contains 10 decimal digits
    resLengthInChars = numberLength * 10 + 1 + 7;
    // Explanation why +1+7:
    // +1 - one char for sign if needed.
    // +7 - For "special case 2" (see below) we have 7 free chars for
    // inserting necessary scaled digits.
    wchar_t* result = new wchar_t[resLengthInChars + 1];
    StackArrayRelease<wchar_t> __st_result(result);

    // allocated [resLengthInChars+1] characters.
    // a free latest character may be used for "special case 1" (see
    // below)
    currentChar = resLengthInChars;
    if (numberLength == 1) {
        int highDigit = digits[0];
        if (highDigit < 0) {
            int64_t v = highDigit & 0xFFFFFFFFL;
            do {
                int64_t prev = v;
                v /= 10;
                result[--currentChar] = (wchar_t) (0x0030 + ((int) (prev - v * 10)));
            } while (v != 0);
        } else {
            int v = highDigit;
            do {
                int prev = v;
                v /= 10;
                result[--currentChar] = (wchar_t) (0x0030 + (prev - v * 10));
            } while (v != 0);
        }
    } else {
        int* temp = new int[numberLength];
        StackArrayRelease<int> __st_temp(temp);

        int tempLen = numberLength;
        arraycopy(digits, 0, temp, 0, tempLen);
        while (true) {
            // divide the array of digits by bigRadix and convert
            // remainders
            // to characters collecting them in the char array
            int64_t result11 = 0;
            for (int i1 = tempLen - 1; i1 >= 0; i1--) {
                int64_t temp1 = (result11 << 32)
                        + (temp[i1] & 0xFFFFFFFFL);
                int64_t res = divideLongByBillion(temp1);
                temp[i1] = (int) res;
                result11 = (int) (res >> 32);
            }
            int resDigit = (int) result11;
            int previous = currentChar;
            do {
                result[--currentChar] = (char) (0x0030 + (resDigit % 10));
            } while (((resDigit /= 10) != 0) && (currentChar != 0));
            int delta = 9 - previous + currentChar;
            for (int i = 0; (i < delta) && (currentChar > 0); i++) {
                result[--currentChar] = L'0';
            }
            int j = tempLen - 1;
            for (; temp[j] == 0; j--) {
                if (j == 0) { // means temp[0] == 0
                    goto BIG_LOOP; //break BIG_LOOP;
                }
            }
            tempLen = j + 1;
        }
        BIG_LOOP:

        while (result[currentChar] == L'0') {
            currentChar++;
        }
    }

    bool negNumber = (sign < 0);
    int exponent = resLengthInChars - currentChar - scale - 1;
    if (scale == 0) {
        if (negNumber) {
            result[--currentChar] = L'-';
        }
        return new UnicodeString(result, currentChar, resLengthInChars
                - currentChar);
    }
    if ((scale > 0) && (exponent >= -6)) {
        if (exponent >= 0) {
            // special case 1
            int insertPoint = currentChar + exponent;
            for (int j = resLengthInChars - 1; j >= insertPoint; j--) {
                result[j + 1] = result[j];
            }
            result[++insertPoint] = L'.';
            if (negNumber) {
                result[--currentChar] = L'-';
            }
            return new UnicodeString(result, currentChar, resLengthInChars
                    - currentChar + 1);
        }
        // special case 2
        for (int j = 2; j < -exponent + 1; j++) {
            result[--currentChar] = L'0';
        }
        result[--currentChar] = L'.';
        result[--currentChar] = L'0';
        if (negNumber) {
            result[--currentChar] = L'-';
        }
        return new UnicodeString(result, currentChar, resLengthInChars
                - currentChar);
    }
    int startPoint = currentChar + 1;
    int endPoint = resLengthInChars;
    UnicodeString* result1 = new UnicodeString(L""); //(16 + endPoint - startPoint);
    if (negNumber) {
        result1->append(L'-');
    }
    if (endPoint - startPoint >= 1) {
        result1->append(result[currentChar]);
        result1->append(L'.');
        result1->append(result, currentChar + 1, resLengthInChars
                - currentChar - 1);
    } else {
        result1->append(result, currentChar, resLengthInChars
                - currentChar);
    }
    result1->append(L'E');
    if (exponent > 0) {
        result1->append(L'+');
    }

    UnicodeString* tstr = Integer::toString(exponent, 10);
    StackRelease<UnicodeString> __st_tstr(tstr);

    result1->append(tstr);
    return result1;

}

int64_t Conversion::divideLongByBillion(int64_t a) {
	int64_t quot;
	int64_t rem;

    if (a >= 0) {
    	int64_t bLong = 1000000000L;
        quot = (a / bLong);
        rem = (a % bLong);
    } else {
        /*
         * Make the dividend positive shifting it right by 1 bit then get
         * the quotient an remainder and correct them properly
         */
    	int64_t aPos = ((uint64_t)a) >> 1;
    	int64_t bPos = ((uint64_t)1000000000L) >> 1;
        quot = aPos / bPos;
        rem = aPos % bPos;
        // double the remainder and add 1 if 'a' is odd
        rem = (rem << 1) + (a & 1);
    }
    return ((rem << 32) | (quot & 0xFFFFFFFFL));
}

void Conversion::arraycopy(int* src, int srcPos, int* dest, int destPos, int length) {
	for(int i = 0; i != length; ++i){
		dest[srcPos + i] = src[destPos + i];
	}
}

} /* namespace alinous */
