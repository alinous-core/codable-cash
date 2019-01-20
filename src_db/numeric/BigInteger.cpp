/*
 * BigInteger.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "numeric/BigInteger.h"

namespace alinous {

BigInteger::BigInteger(int sign, int value) {
    this->sign = sign;
    this->numberLength = 1;
    this->digits = new int[1] { value };
}

BigInteger::BigInteger(UnicodeString* val, int radix) {

}

BigInteger::~BigInteger() {
	if(this->digits){
		delete [] this->digits;
	}
}
} /* namespace alinous */
