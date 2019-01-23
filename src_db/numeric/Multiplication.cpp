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
	BigInteger res(10);

	return res.pow(exp);
}

} /* namespace alinous */
