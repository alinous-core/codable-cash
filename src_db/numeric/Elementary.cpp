/*
 * Elementary.cpp
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#include "numeric/Elementary.h"
#include "numeric/BigInteger.h"

namespace alinous {

int alinous::Elementary::inplaceAdd(int* a, int aSize, int addend) {
    int64_t carry = addend & 0xFFFFFFFFL;

    for (int i = 0; (carry != 0) && (i < aSize); i++) {
        carry += a[i] & 0xFFFFFFFFL;
        a[i] = (int) carry;
        carry >>= 32;
    }
    return (int) carry;
}

BigInteger Elementary::subtract(const BigInteger& op1, const BigInteger& op2) {
	int resSign;
	int* resDigits;
	int op1Sign = op1.sign;
	int op2Sign = op2.sign;

	if (op2Sign == 0) {
		return op1;
	}
	if (op1Sign == 0) {
		return op2.negate();
	}
	int op1Len = op1.numberLength;
	int op2Len = op2.numberLength;
	if (op1Len + op2Len == 2) {
		int64_t a = ( op1.digits[0] & 0xFFFFFFFFL );
		int64_t b = ( op2.digits[0] & 0xFFFFFFFFL );
		if (op1Sign < 0) {
			a = -a;
		}
		if (op2Sign < 0) {
			b = -b;
		}
		return BigInteger::valueOf(a - b);
	}
	int cmp = ( ( op1Len != op2Len ) ? ( ( op1Len > op2Len ) ? 1 : -1 )
			: Elementary::compareArrays (op1.digits, op2.digits, op1Len) );

	int resDigits_length = 0;
	if (cmp == BigInteger::LESS) {
		resSign = -op2Sign;
		resDigits = ( op1Sign == op2Sign ) ? subtract (op2.digits, op2Len,
				op1.digits, op1Len) : add (op2.digits, op2Len, op1.digits,
				op1Len);
		resDigits_length = op2Len;
	} else {
		resSign = op1Sign;
		if (op1Sign == op2Sign) {
			if (cmp == BigInteger::EQUALS) {
				return BigInteger::ZERO; // new BigInteger(0, 0);
			}
			resDigits = subtract (op1.digits, op1Len, op2.digits, op2Len);
			resDigits_length = op1Len;
		} else {
			resDigits = add(op1.digits, op1Len, op2.digits, op2Len);
			resDigits_length = op1Len;
		}
	}
	// BigInteger* res = new BigInteger (resSign, resDigits.length, resDigits);
	 BigInteger res(resSign, resDigits_length, resDigits);
	res.cutOffLeadingZeroes ();
	return res;
}

int* Elementary::subtract(int* a, int aSize, int* b, int bSize) {
    // PRE: a[] >= b[]
    int* res = new int[aSize]{};
    subtract(res, a, aSize, b, bSize);
    return res;
}

BigInteger Elementary::add(BigInteger& op1, BigInteger& op2) {
    int* resDigits;
    int resSign;
    int op1Sign = op1.sign;
    int op2Sign = op2.sign;

    if (op1Sign == 0) {
        return op2;
    }
    if (op2Sign == 0) {
        return op1;
    }
    int op1Len = op1.numberLength;
    int op2Len = op2.numberLength;

    int resDigits_length = 0;
    if (op1Len + op2Len == 2) {
        int64_t a = (op1.digits[0] & 0xFFFFFFFFL);
        int64_t b = (op2.digits[0] & 0xFFFFFFFFL);

        if (op1Sign == op2Sign) {
        	int64_t res = a + b;
        	int valueLo = (int) res;
        	int valueHi = (int) (((uint64_t)res) >> 32);

            int param[2]{ valueLo, valueHi };

            return ((valueHi == 0) ? BigInteger(op1Sign, valueLo)
                    : BigInteger(op1Sign, 2, param));
        }
        return BigInteger::valueOf((op1Sign < 0) ? (b - a) : (a - b));
    } else if (op1Sign == op2Sign) {
        resSign = op1Sign;
        // an augend should not be shorter than addend
        resDigits = (op1Len >= op2Len) ? add(op1.digits, op1Len,
                op2.digits, op2Len) : add(op2.digits, op2Len, op1.digits,
                op1Len);
        resDigits_length = (op1Len >= op2Len) ? op1Len + 1 : op2Len + 1;
    } else { // signs are different
        int cmp = ((op1Len != op2Len) ? ((op1Len > op2Len) ? 1 : -1)
                : compareArrays(op1.digits, op2.digits, op1Len));

        if (cmp == BigInteger::EQUALS) {
            return BigInteger::ZERO;
        }
        // a minuend should not be shorter than subtrahend
        if (cmp == BigInteger::GREATER) {
            resSign = op1Sign;
            resDigits = subtract(op1.digits, op1Len, op2.digits, op2Len);
            resDigits_length = op1Len;
        } else {
            resSign = op2Sign;
            resDigits = subtract(op2.digits, op2Len, op1.digits, op1Len);
            resDigits_length = op2Len;
        }
    }
    //BigInteger* res = new BigInteger(resSign, resDigits.length, resDigits);
    BigInteger res(resSign, resDigits_length, resDigits);
    res.cutOffLeadingZeroes();
    return res;
}

int* Elementary::add(int* a, int aSize, int* b, int bSize) {
    // PRE: a[] >= b[]
    int* res = new int[aSize + 1]{};
    add(res, a, aSize, b, bSize);
    return res;
}

void Elementary::add(int* res, int* a, int aSize, int* b, int bSize) {
	// PRE: a.length < max(aSize, bSize)

    int i;
	int64_t carry = ( a[0] & 0xFFFFFFFFL ) + ( b[0] & 0xFFFFFFFFL );

    res[0] = (int) carry;
    carry >>= 32;

	if (aSize >= bSize) {
    for (i = 1; i < bSize; i++) {
			carry += ( a[i] & 0xFFFFFFFFL ) + ( b[i] & 0xFFFFFFFFL );
        res[i] = (int) carry;
        carry >>= 32;
    }
    for (; i < aSize; i++) {
        carry += a[i] & 0xFFFFFFFFL;
        res[i] = (int) carry;
        carry >>= 32;
    }
	} else {
		for (i = 1; i < aSize; i++) {
			carry += ( a[i] & 0xFFFFFFFFL ) + ( b[i] & 0xFFFFFFFFL );
    res[i] = (int) carry;
			carry >>= 32;
		}
		for (; i < bSize; i++) {
			carry += b[i] & 0xFFFFFFFFL;
			res[i] = (int) carry;
			carry >>= 32;
		}
	}
	if (carry != 0) {
		res[i] = (int) carry;
	}
}

void alinous::Elementary::subtract(int* res, int* a, int aSize, int* b, int bSize) {
	int i;
	int64_t borrow = 0;

	for (i = 0; i < bSize; i++) {
		borrow += ( a[i] & 0xFFFFFFFFL ) - ( b[i] & 0xFFFFFFFFL );
		res[i] = (int) borrow;
		borrow >>= 32; // -1 or 0
	}
	for (; i < aSize; i++) {
		borrow += a[i] & 0xFFFFFFFFL;
		res[i] = (int) borrow;
		borrow >>= 32; // -1 or 0
	}
}

int alinous::Elementary::compareArrays(int* a, int* b, int size) {
    int i;
    for (i = size - 1; (i >= 0) && (a[i] == b[i]); i--) {
        ;
    }
    return ((i < 0) ? BigInteger::EQUALS
            : (a[i] & 0xFFFFFFFFL) < (b[i] & 0xFFFFFFFFL) ? BigInteger::LESS
                    : BigInteger::GREATER);
}


} /* namespace alinous */
