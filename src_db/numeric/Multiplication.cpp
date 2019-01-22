/*
 * Multiplication.cpp
 *
 *  Created on: 2019/01/22
 *      Author: iizuka
 */

#include "numeric/Multiplication.h"
#include "numeric/BigInteger.h"

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
	        __bigTenPows.addElement(new BigInteger( __bigTenPows.get(i - 1)->multiply(BigInteger(10))));
	    }

		init = true;
	}

	if(ten){
		return __bigTenPows.getRoot();
	}
	return __bigFivePows.getRoot();
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
        return BigInteger(BigInteger(10)).pow(intExp);
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

} /* namespace alinous */
