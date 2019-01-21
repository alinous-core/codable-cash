/*
 * Division.h
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#ifndef NUMERIC_DIVISION_H_
#define NUMERIC_DIVISION_H_

#include <inttypes.h>

namespace alinous {

class Division {
public:
	static int divideArrayByInt(int* dest, int* src, const int srcLength, const int divisor);
	static int64_t divideLongByInt(int64_t a, int b);
	static int multiplyAndSubtract(int* a, int start, int* b, int bLen, int c);
    static int* divide(int* quot, int quotLength, int* a, int aLength, int* b, int bLength);

    static void arraycopy(int* src, int srcPos, int* dest, int destPos, int length);
};

} /* namespace alinous */

#endif /* NUMERIC_DIVISION_H_ */
