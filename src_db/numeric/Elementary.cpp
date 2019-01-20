/*
 * Elementary.cpp
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#include "numeric/Elementary.h"

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

} /* namespace alinous */


