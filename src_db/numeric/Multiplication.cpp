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

#include "base/ArrayList.h"
#include "base/StackRelease.h"

namespace alinous {

const BigInteger** Multiplication::bigTenPows = initbigpows(true);
const BigInteger** Multiplication::bigFivePows = initbigpows(false);

const BigInteger** Multiplication::initbigpows(bool ten) {
	static bool init = false;
	static ArrayList<const BigInteger> __bigFivePows(32);
	static ArrayList<const BigInteger> __bigTenPows(32);

	if(!init){
	    int i;
	    int64_t fivePow = 1L;

	    __bigFivePows.setDeleteOnExit();
	    __bigTenPows.setDeleteOnExit();

	    for (i = 0; i <= 18; i++) {
	        __bigFivePows.addElement(new BigInteger(BigInteger::valueOf(fivePow)));
	        __bigTenPows.addElement(new BigInteger(BigInteger::valueOf(fivePow << i)));
	        fivePow *= 5;
	    }
	    for (; i < /*bigTenPows.length*/32; i++) {
	        __bigFivePows.addElement(new BigInteger( __bigFivePows.get(i - 1)->multiply(*__bigFivePows.get(1))));
	        __bigTenPows.addElement(new BigInteger( __bigTenPows.get(i - 1)->multiply(BigInteger::TEN)));
	    }

		init = true;
	}

	if(ten){
		return __bigTenPows.getRoot();
	}
	return __bigFivePows.getRoot();

/*    int i;
    int64_t fivePow = 1L;

    for (i = 0; i <= 18; i++) {
        bigFivePows[i] = BigInteger::valueOf(fivePow);
        bigTenPows[i] = BigInteger::valueOf(fivePow << i);
        fivePow *= 5;
    }
   // for (; i < bigTenPows.length; i++) {
    for (; i < 32; i++) {
        bigFivePows[i] = bigFivePows[i - 1]->multiply(bigFivePows[1]);
        bigTenPows[i] = bigTenPows[i - 1]->multiply(&BigInteger::TEN);
    }
*/
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
	return ((uint64_t)a & 0xFFFFFFFFL) * ((uint64_t)b & 0xFFFFFFFFL) + ((uint64_t)c & 0xFFFFFFFFL) + ((uint64_t)d & 0xFFFFFFFFL);
}

BigInteger Multiplication::powerOf10(int64_t exp) {
    // PRE: exp >= 0
	StackMultipleRelease<BigInteger> _st_bint;

	int intExp = (int)exp;
    // "SMALL POWERS"
    if (exp < /*bigTenPows.length*/ 32) {
        // The largest power that fit in 'long' type
        return BigInteger(*bigTenPows[intExp]);
    } else if (exp <= 50) {
        // To calculate:    10^exp
        return BigInteger(BigInteger::TEN).pow(intExp);
    } else if (exp <= 1000) {
        // To calculate:    5^exp * 2^exp
        return BigInteger(*bigFivePows[1]).pow(intExp).shiftLeft(intExp);
    }
    // "LARGE POWERS"
    /*
     * To check if there is free memory to allocate a BigInteger of the
     * estimated size, measured in bytes: 1 + [exp / log10(2)]
     */

    long byteArraySize = 1 + (long)(exp / 2.4082399653118496);

    //if (byteArraySize > Runtime.getRuntime().freeMemory()) {
        // math.01=power of ten too big
     //   throw new ArithmeticException(Messages.getString("math.01")); //$NON-NLS-1$
    //}
    if (exp <= Integer::MAX_VALUE) {
        // To calculate:    5^exp * 2^exp
        return BigInteger(*bigFivePows[1]).pow(intExp).shiftLeft(intExp);
    }

    /*
     * "HUGE POWERS"
     *
     * This branch probably won't be executed since the power of ten is too
     * big.
     */
    // To calculate:    5^exp
    BigInteger powerOfFive = BigInteger(*bigFivePows[1]).pow(Integer::MAX_VALUE);
    BigInteger res = powerOfFive;
    int64_t longExp = exp - Integer::MAX_VALUE;

    intExp = (int)(exp % Integer::MAX_VALUE);
    while (longExp > Integer::MAX_VALUE) {
        res = res.multiply(powerOfFive);
        longExp -= Integer::MAX_VALUE;
    }
    res = res.multiply(BigInteger(*bigFivePows[1]).pow(intExp));
    // To calculate:    5^exp << exp
    res = res.shiftLeft(Integer::MAX_VALUE);
    longExp = exp - Integer::MAX_VALUE;
    while (longExp > Integer::MAX_VALUE) {
        res = res.shiftLeft(Integer::MAX_VALUE);
        longExp -= Integer::MAX_VALUE;
    }
    res = res.shiftLeft(intExp);
    return res;

}

BigInteger Multiplication::multiply(const BigInteger& x, const BigInteger& y) {
	return karatsuba(x, y);
}

BigInteger Multiplication::karatsuba(BigInteger op1, BigInteger op2) {
    if (op2.numberLength > op1.numberLength) {
    	BigInteger temp = op1;
        op1 = op2;
        op2 = temp;
    }
    if (op2.numberLength < whenUseKaratsuba) {
        return multiplyPAP(op1, op2);
    }
    /*  Karatsuba:  u = u1*B + u0
     *              v = v1*B + v0
     *  u*v = (u1*v1)*B^2 + ((u1-u0)*(v0-v1) + u1*v1 + u0*v0)*B + u0*v0
     */
    // ndiv2 = (op1.numberLength / 2) * 32
    int ndiv2 = (op1.numberLength & 0xFFFFFFFE) << 4;
    BigInteger upperOp1 = op1.shiftRight(ndiv2);
    BigInteger upperOp2 = op2.shiftRight(ndiv2);
    BigInteger lowerOp1 = op1.subtract(upperOp1.shiftLeft(ndiv2));
    BigInteger lowerOp2 = op2.subtract(upperOp2.shiftLeft(ndiv2));

    BigInteger upper = karatsuba(upperOp1, upperOp2);
    BigInteger lower = karatsuba(lowerOp1, lowerOp2);
    BigInteger middle = karatsuba( upperOp1.subtract(lowerOp1),
            lowerOp2.subtract(upperOp2));

    middle = middle.add(upper).add(lower);
    middle = middle.shiftLeft(ndiv2);
    upper = upper.shiftLeft(ndiv2 << 1);

    return upper.add(middle).add(lower);
}

BigInteger Multiplication::multiplyPAP(const BigInteger& a, const BigInteger& b) {
    int aLen = a.numberLength;
    int bLen = b.numberLength;
    int resLength = aLen + bLen;
    int resSign = (a.sign != b.sign) ? -1 : 1;
    // A special case when both numbers don't exceed int
    if (resLength == 2) {
        int64_t val = unsignedMultAddAdd(a.digits[0], b.digits[0], 0, 0);
        int valueLo = (int)val;
        int valueHi = (int)( ((uint64_t)val) >> 32);
        int* param = new int[2]{valueLo, valueHi};
        StackArrayRelease<int> __st_param(param);

        return ((valueHi == 0)
			? BigInteger(resSign, valueLo)
			: BigInteger(resSign, 2, param));
    }
    int* aDigits = a.digits;
    int* bDigits = b.digits;
    int* resDigits = new int[resLength]{};
    StackArrayRelease<int> __st_resDigits(resDigits);

    // Common case
    multArraysPAP(aDigits, aLen, bDigits, bLen, resDigits);
    BigInteger result(resSign, resLength, resDigits);
    result.cutOffLeadingZeroes();
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

BigInteger Multiplication::pow(const BigInteger& base, int exponent) {
    // PRE: exp > 0
    BigInteger res(BigInteger::ONE);
    BigInteger acc = base;

    for (; exponent > 1; exponent >>= 1) {
        if ((exponent & 1) != 0) {
            // if odd, multiply one more time by acc
            res = res.multiply(acc);
        }
        // acc = base^(2^i)
        //a limit where karatsuba performs a faster square than the square algorithm
        if ( acc.numberLength == 1 ){
            acc = acc.multiply(acc); // square
        }
        else{
        	int newLength = acc.numberLength<<1;
        	int* sqres = new int [newLength]{};
        	square(acc.digits, acc.numberLength, sqres);
            acc = BigInteger(1, newLength, sqres);
        }
    }
    // exponent == 1, multiply one more time
    res = res.multiply(acc);
    return res;
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
