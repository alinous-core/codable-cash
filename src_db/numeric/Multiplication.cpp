/*
 * Multiplication.cpp
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#include "numeric/Multiplication.h"
#include "numeric/BigInteger.h"
#include "numeric/BitLevel.h"
#include "base/Integer.h"

namespace alinous {

const BigInteger* Multiplication::bigTenPows[32]{};
const BigInteger* Multiplication::bigFivePows[32]{};

void Multiplication::initbigpows() {

    int i;
    int64_t fivePow = 1L;

    for (i = 0; i <= 18; i++) {
        bigFivePows[i] = BigInteger::valueOf(fivePow);
        bigTenPows[i] = BigInteger::valueOf(fivePow << i);
        fivePow *= 5;
    }
    for (; i < /*bigTenPows.length*/32; i++) {
        bigFivePows[i] = bigFivePows[i - 1]->multiply(bigFivePows[1]);
        bigTenPows[i] = bigTenPows[i - 1]->multiply(&BigInteger::TEN);
    }
}

int Multiplication::multiplyByInt(int* a, int aSize, int factor) {
	return multiplyByInt(a, a, aSize, factor);
}

int Multiplication::multiplyByInt(int* res, int* a, int aSize, int factor) {
	int64_t carry = 0;
    for (int i = 0; i < aSize; i++) {
        carry = unsignedMultAddAdd(a[i], factor, (int)carry, 0);
        res[i] = (int)carry;
        //carry >>>= 32;
        carry = ((uint64_t)carry) >> 32;
    }
    return (int)carry;
}

int64_t Multiplication::unsignedMultAddAdd(int a, int b, int c, int d) {
	return (a & 0xFFFFFFFFL) * (b & 0xFFFFFFFFL) + (c & 0xFFFFFFFFL) + (d & 0xFFFFFFFFL);
}

BigInteger* Multiplication::powerOf10(int64_t exp) {
	// FIXME

    // PRE: exp >= 0
   /*int intExp = (int)exp;
    // "SMALL POWERS"
    if (exp < bigTenPows.length) {
        // The largest power that fit in 'long' type
        return bigTenPows[intExp];
    } else if (exp <= 50) {
        // To calculate:    10^exp
        return BigInteger.TEN.pow(intExp);
    } else if (exp <= 1000) {
        // To calculate:    5^exp * 2^exp
        return bigFivePows[1].pow(intExp).shiftLeft(intExp);
    }
    // "LARGE POWERS"
    /*
     * To check if there is free memory to allocate a BigInteger of the
     * estimated size, measured in bytes: 1 + [exp / log10(2)]
     */
	/*
    long byteArraySize = 1 + (long)(exp / 2.4082399653118496);

    if (byteArraySize > Runtime.getRuntime().freeMemory()) {
        // math.01=power of ten too big
        throw new ArithmeticException(Messages.getString("math.01")); //$NON-NLS-1$
    }
    if (exp <= Integer.MAX_VALUE) {
        // To calculate:    5^exp * 2^exp
        return bigFivePows[1].pow(intExp).shiftLeft(intExp);
    }
    */
    /*
     * "HUGE POWERS"
     *
     * This branch probably won't be executed since the power of ten is too
     * big.
     */
    // To calculate:    5^exp
    /*
    BigInteger* powerOfFive = bigFivePows[1].pow(Integer.MAX_VALUE);
    BigInteger* res = powerOfFive;
    long longExp = exp - Integer::MAX_VALUE;

    intExp = (int)(exp % Integer::MAX_VALUE);
    while (longExp > Integer::MAX_VALUE) {
        res = res.multiply(powerOfFive);
        longExp -= Integer::MAX_VALUE;
    }
    res = res->multiply(bigFivePows[1].pow(intExp));
    // To calculate:    5^exp << exp
    res = res->shiftLeft(Integer.MAX_VALUE);
    longExp = exp - Integer::MAX_VALUE;
    while (longExp > Integer::MAX_VALUE) {
        res = res.shiftLeft(Integer::MAX_VALUE);
        longExp -= Integer::MAX_VALUE;
    }
    res = res::shiftLeft(intExp);
    return res;
    */
}

BigInteger* Multiplication::multiply(const BigInteger* x, const BigInteger* y) {
	return karatsuba(x, y);
}

BigInteger* Multiplication::karatsuba(const BigInteger* op1, const BigInteger* op2) {
	const BigInteger* temp = nullptr;
    if (op2->numberLength > op1->numberLength) {
        temp = op1;
        op1 = op2;
        op2 = temp;
    }
    if (op2->numberLength < whenUseKaratsuba) {
        return multiplyPAP(op1, op2);
    }
    /*  Karatsuba:  u = u1*B + u0
     *              v = v1*B + v0
     *  u*v = (u1*v1)*B^2 + ((u1-u0)*(v0-v1) + u1*v1 + u0*v0)*B + u0*v0
     */
    // ndiv2 = (op1.numberLength / 2) * 32
    int ndiv2 = (op1->numberLength & 0xFFFFFFFE) << 4;
    BigInteger* upperOp1 = op1->shiftRight(ndiv2);
    BigInteger* upperOp2 = op2->shiftRight(ndiv2);
    BigInteger* lowerOp1 = op1->subtract(upperOp1->shiftLeft(ndiv2));
    BigInteger* lowerOp2 = op2->subtract(upperOp2->shiftLeft(ndiv2));

    BigInteger* upper = karatsuba(upperOp1, upperOp2);
    BigInteger* lower = karatsuba(lowerOp1, lowerOp2);
    BigInteger* middle = karatsuba( upperOp1->subtract(lowerOp1),
            lowerOp2->subtract(upperOp2));
    middle = middle->add(upper)->add(lower);
    middle = middle->shiftLeft(ndiv2);
    upper = upper->shiftLeft(ndiv2 << 1);

    return upper->add(middle)->add(lower);
}

BigInteger* Multiplication::multiplyPAP(const BigInteger* a, const BigInteger* b) {
    int aLen = a->numberLength;
    int bLen = b->numberLength;
    int resLength = aLen + bLen;
    int resSign = (a->sign != b->sign) ? -1 : 1;
    // A special case when both numbers don't exceed int
    if (resLength == 2) {
        int64_t val = unsignedMultAddAdd(a->digits[0], b->digits[0], 0, 0);
        int valueLo = (int)val;
        int valueHi = (int)( ((uint64_t)val) >> 32);
        int* param = new int[2]{valueLo, valueHi};

        return ((valueHi == 0)
			? new BigInteger(resSign, valueLo)
			: new BigInteger(resSign, 2, param));
    }
    int* aDigits = a->digits;
    int* bDigits = b->digits;
    int* resDigits = new int[resLength];
    // Common case
    multArraysPAP(aDigits, aLen, bDigits, bLen, resDigits);
    BigInteger* result = new BigInteger(resSign, resLength, resDigits);
    result->cutOffLeadingZeroes();
    return result;
}

void Multiplication::multArraysPAP(int* aDigits, int aLen, int* bDigits, int bLen, int* resDigits) {
    if(aLen == 0 || bLen == 0) return;

    if(aLen == 1) {
        resDigits[bLen] = multiplyByInt(resDigits, bDigits, bLen, aDigits[0]);
    } else if(bLen == 1) {
        resDigits[aLen] = multiplyByInt(resDigits, aDigits, aLen, bDigits[0]);
    } else {
        multPAP(aDigits, bDigits, resDigits, aLen, bLen);
    }
}

void Multiplication::multPAP(int* a, int* b, int* t, int aLen, int bLen) {
    if(a == b && aLen == bLen) {
        square(a, aLen, t);
        return;
    }

    for(int i = 0; i < aLen; i++){
        int64_t carry = 0;
        int aI = a[i];
        for (int j = 0; j < bLen; j++){
           carry = unsignedMultAddAdd(aI, b[j], t[i+j], (int)carry);
           t[i+j] = (int) carry;
           carry = ((uint64_t)carry) >> 32;
           //carry >>>= 32;
         }
         t[i+bLen] = (int) carry;
    }
}

int* Multiplication::square(int* a, int aLen, int* res) {
    int64_t carry;

    for(int i = 0; i < aLen; i++){
        carry = 0;
        for (int j = i+1; j < aLen; j++){
            carry = unsignedMultAddAdd(a[i], a[j], res[i+j], (int)carry);
            res[i+j] = (int) carry;
            carry = ((uint64_t)carry) >> 32;
            // carry >>>= 32;
        }
        res[i+aLen] = (int) carry;
    }

    BitLevel::shiftLeftOneBit(res, res, aLen << 1);

    carry = 0;
    for(int i = 0, index = 0; i < aLen; i++, index++){
        carry = unsignedMultAddAdd(a[i], a[i], res[index],(int)carry);
        res[index] = (int) carry;
        carry = ((uint64_t)carry) >> 32;
        //carry >>>= 32;
        index++;
        carry += res[index] & 0xFFFFFFFFL;
        res[index] = (int)carry;
        carry = ((uint64_t)carry) >> 32;
        //carry >>>= 32;
    }
    return res;
}

} /* namespace alinous */
