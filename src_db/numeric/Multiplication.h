/*
 * Multiplication.h
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#ifndef NUMERIC_MULTIPLICATION_H_
#define NUMERIC_MULTIPLICATION_H_

#include <inttypes.h>

namespace alinous {

class BigInteger;

class Multiplication {
public:
	static const constexpr int whenUseKaratsuba{63};

	static int multiplyByInt(int* a, int aSize, int factor);
	static int multiplyByInt(int* res, int* a, int aSize, int factor);
	static int64_t unsignedMultAddAdd(int a, int b, int c, int d);
	static BigInteger* powerOf10(int64_t exp);
	static BigInteger* multiply(BigInteger* x, BigInteger* y);
	static BigInteger* karatsuba(BigInteger* op1, BigInteger* op2);
	static BigInteger* multiplyPAP(BigInteger* a, BigInteger* b);
	static void multArraysPAP(int* aDigits, int aLen, int* bDigits, int bLen, int* resDigits);
	static void multPAP(int* a, int* b, int* t, int aLen, int bLen);

	static int* square(int* a, int aLen, int* res);

};

} /* namespace alinous */

#endif /* NUMERIC_MULTIPLICATION_H_ */
