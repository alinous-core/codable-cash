/*
 * Division.cpp
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#include "numeric/Division.h"
#include "numeric/BitLevel.h"
#include "numeric/Multiplication.h"
#include "base/Integer.h"

namespace alinous {

int Division::divideArrayByInt(int* dest, int* src, const int srcLength, const int divisor) {
    int64_t rem = 0;
    int64_t bLong = divisor & 0xffffffffL;

    for (int i = srcLength - 1; i >= 0; i--) {
        int64_t temp = (rem << 32) | (src[i] & 0xffffffffL);
        int64_t quot;
        if (temp >= 0) {
            quot = (temp / bLong);
            rem = (temp % bLong);
        } else {
            /*
             * make the dividend positive shifting it right by 1 bit then
             * get the quotient an remainder and correct them properly
             */
            int64_t aPos = ((uint64_t)temp) >> 1;
            int64_t bPos = ((uint64_t)divisor) >> 1;
            quot = aPos / bPos;
            rem = aPos % bPos;
            // double the remainder and add 1 if a is odd
            rem = (rem << 1) + (temp & 1);
            if ((divisor & 1) != 0) {
                // the divisor is odd
                if (quot <= rem) {
                    rem -= quot;
                } else {
                    if (quot - rem <= bLong) {
                        rem += bLong - quot;
                        quot -= 1;
                    } else {
                        rem += (bLong << 1) - quot;
                        quot -= 2;
                    }
                }
            }
        }
        dest[i] = (int) (quot & 0xffffffffL);
    }
    return (int) rem;
}

int* Division::divide(int* quot, int quotLength, int* a, int aLength, int* b, int bLength) {
    int* normA = new int[aLength + 1]{}; // the normalized dividend
    // an extra byte is needed for correct shift
    int* normB = new int[bLength + 1]{}; // the normalized divisor;
    int normBLength = bLength;
    /*
     * Step D1: normalize a and b and put the results to a1 and b1 the
     * normalized divisor's first digit must be >= 2^31
     */
    int divisorShift = Integer::numberOfLeadingZeros(b[bLength - 1]);
    if (divisorShift != 0) {
        BitLevel::shiftLeft(normB, bLength + 1, b, 0, divisorShift);
        BitLevel::shiftLeft(normA, aLength + 1, a, 0, divisorShift);
    } else {
        arraycopy(a, 0, normA, 0, aLength);
        arraycopy(b, 0, normB, 0, bLength);
    }
    int firstDivisorDigit = normB[normBLength - 1];
    // Step D2: set the quotient index
    int i = quotLength - 1;
    int j = aLength;

    while (i >= 0) {
        // Step D3: calculate a guess digit guessDigit
        int guessDigit = 0;
        if (normA[j] == firstDivisorDigit) {
            // set guessDigit to the largest unsigned int value
            guessDigit = -1;
        } else {
            int64_t product = (((normA[j] & 0xffffffffL) << 32) + (normA[j - 1] & 0xffffffffL));
            int64_t res = Division::divideLongByInt(product, firstDivisorDigit);
            guessDigit = (int) res; // the quotient of divideLongByInt
            int rem = (int) (res >> 32); // the remainder of
                                            // divideLongByInt
            // decrease guessDigit by 1 while leftHand > rightHand
            if (guessDigit != 0) {
                int64_t leftHand = 0;
                int64_t rightHand = 0;
                bool rOverflowed = false;
                guessDigit++; // to have the proper value in the loop
                                // below
                do {
                    guessDigit--;
                    if (rOverflowed) {
                        break;
                    }
                    // leftHand always fits in an unsigned long
                    leftHand = (guessDigit & 0xffffffffL)
                            * (normB[normBLength - 2] & 0xffffffffL);
                    /*
                     * rightHand can overflow; in this case the loop
                     * condition will be true in the next step of the loop
                     */
                    rightHand = ((long) rem << 32)
                            + (normA[j - 2] & 0xffffffffL);
                    int64_t longR = (rem & 0xffffffffL)
                            + (firstDivisorDigit & 0xffffffffL);
                    /*
                     * checks that longR does not fit in an unsigned int;
                     * this ensures that rightHand will overflow unsigned
                     * long in the next step
                     */
                    if (Integer::numberOfLeadingZeros((int) (((uint64_t)longR) >> 32)) < 32) {
                        rOverflowed = true;
                    } else {
                        rem = (int) longR;
                    }
                } while (((leftHand ^ 0x8000000000000000L) > (rightHand ^ 0x8000000000000000L)));
            }
        }
        // Step D4: multiply normB by guessDigit and subtract the production
        // from normA.
        if (guessDigit != 0) {
            int borrow = Division::multiplyAndSubtract(normA, j
                    - normBLength, normB, normBLength,
                    guessDigit);
            // Step D5: check the borrow
            if (borrow != 0) {
                // Step D6: compensating addition
                guessDigit--;
                int64_t carry = 0;
                for (int k = 0; k < normBLength; k++) {
                    carry += (normA[j - normBLength + k] & 0xffffffffL)
                            + (normB[k] & 0xffffffffL);
                    normA[j - normBLength + k] = (int) carry;
                    //carry >>>= 32;
                    carry = ((uint64_t)carry) >> 32;
                }
            }
        }
        if (quot != nullptr) {
            quot[i] = guessDigit;
        }
        // Step D7
        j--;
        i--;
    }
    /*
     * Step D8: we got the remainder in normA. Denormalize it id needed
     */
    if (divisorShift != 0) {
        // reuse normB
        BitLevel::shiftRight(normB, normBLength, normA, 0, divisorShift);
        return normB;
    }
    arraycopy(normA, 0, normB, 0, bLength);
    return normA;
}

int64_t Division::divideLongByInt(int64_t a, int b) {
	int64_t quot;
	int64_t rem;
	int64_t bLong = b & 0xffffffffL;

    if (a >= 0) {
        quot = (a / bLong);
        rem = (a % bLong);
    } else {
        /*
         * Make the dividend positive shifting it right by 1 bit then get
         * the quotient an remainder and correct them properly
         */
    	int64_t aPos = ((uint64_t)a) >> 1;
    	int64_t bPos = ((uint64_t)b) >> 1;
        quot = aPos / bPos;
        rem = aPos % bPos;
        // double the remainder and add 1 if a is odd
        rem = (rem << 1) + (a & 1);
        if ((b & 1) != 0) { // the divisor is odd
            if (quot <= rem) {
                rem -= quot;
            } else {
                if (quot - rem <= bLong) {
                    rem += bLong - quot;
                    quot -= 1;
                } else {
                    rem += (bLong << 1) - quot;
                    quot -= 2;
                }
            }
        }
    }
    return (rem << 32) | (quot & 0xffffffffL);
}

int Division::multiplyAndSubtract(int* a, int start, int* b, int bLen, int c) {
    int64_t carry0 = 0;
    int64_t carry1 = 0;

    for (int i = 0; i < bLen; i++) {
        carry0 = Multiplication::unsignedMultAddAdd(b[i], c, (int)carry0, 0);
        carry1 = (a[start+i] & 0xffffffffL) - (carry0 & 0xffffffffL) + carry1;
        a[start+i] = (int)carry1;
        carry1 >>=  32; // -1 or 0
        carry0 = ((uint64_t)carry0) >> 32;
        //carry0 >>>= 32;
    }

    carry1 = (a[start + bLen] & 0xffffffffL) - carry0 + carry1;
    a[start + bLen] = (int)carry1;
    return (int)(carry1 >> 32); // -1 or 0
}

void Division::arraycopy(int* src, int srcPos, int* dest, int destPos, int length) {
	for(int i = 0; i != length; ++i){
		dest[destPos + i] = src[srcPos + i];
	}
}

} /* namespace alinous */

