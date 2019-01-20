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

class Multiplication {
public:
	static int multiplyByInt(int* a, int aSize, int factor);
	static int multiplyByInt(int* res, int* a, int aSize, int factor);
	static int64_t unsignedMultAddAdd(int a, int b, int c, int d);
};

} /* namespace alinous */

#endif /* NUMERIC_MULTIPLICATION_H_ */
