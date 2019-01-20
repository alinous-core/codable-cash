/*
 * Multiplication.cpp
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#include "numeric/Multiplication.h"

namespace alinous {

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

} /* namespace alinous */

