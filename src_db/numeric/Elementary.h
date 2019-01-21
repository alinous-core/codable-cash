/*
 * Elementary.h
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#ifndef NUMERIC_ELEMENTARY_H_
#define NUMERIC_ELEMENTARY_H_

#include <inttypes.h>

namespace alinous {

class BigInteger;

class Elementary {
public:
	static int inplaceAdd(int* a, int aSize, int addend);
	static BigInteger* subtract(BigInteger* op1, BigInteger* op2);
	static int compareArrays(int* a, int* b, int size);

	static BigInteger* add(BigInteger* op1, BigInteger* op2);
	static int* add(int* a, int aSize, int* b, int bSize);
	static void add(int* res, int* a, int aSize, int* b, int bSize);

	static int* subtract(int* a, int aSize, int* b, int bSize);
	static void subtract(int* res, int* a, int aSize, int* b, int bSize);
};

} /* namespace alinous */

#endif /* NUMERIC_ELEMENTARY_H_ */
