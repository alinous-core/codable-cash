/*
 * BitLevel.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "numeric/BitLevel.h"
#include "numeric/BigInteger.h"
#include "base/Integer.h"

namespace alinous {

BitLevel::BitLevel() {
}

BitLevel::~BitLevel() {
}

int BitLevel::bitLength(BigInteger* val) {
    if (val->sign == 0) {
        return 0;
    }
    int bLength = (val->numberLength << 5);
    int highDigit = val->digits[val->numberLength - 1];

    if (val->sign < 0) {
        int i = val->getFirstNonzeroDigit();
        // We reduce the problem to the positive case.
        if (i == val->numberLength - 1) {
            highDigit--;
        }
    }
    // Subtracting all sign bits
    bLength -= Integer::numberOfLeadingZeros(highDigit);
    return bLength;
}

} /* namespace alinous */
