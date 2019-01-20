/*
 * BigInteger.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef NUMERIC_BIGINTEGER_H_
#define NUMERIC_BIGINTEGER_H_

#include <inttypes.h>

namespace alinous {

class UnicodeString;

class BigInteger {
public:
	BigInteger(int sign, int value);
	BigInteger(UnicodeString* val, int radix);
	virtual ~BigInteger();

private:
	int numberLength;
	int sign;
	int* digits;
};

} /* namespace alinous */

#endif /* NUMERIC_BIGINTEGER_H_ */
