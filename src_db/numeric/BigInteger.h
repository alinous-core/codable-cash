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
class BitLevel;

class BigInteger {
public:
	friend class BitLevel;

	BigInteger(const BigInteger& inst) = delete;

	BigInteger(int sign, int value);
	explicit BigInteger(UnicodeString* val);
	BigInteger(UnicodeString* val, int radix);
	virtual ~BigInteger();

	int bitLength();
	int getFirstNonzeroDigit();

	int64_t longValue();

private:
	static void setFromString(BigInteger* bi, UnicodeString* val, int radix);
	void cutOffLeadingZeroes();

private:
	int numberLength;
	int sign;
	int* digits;
	int firstNonzeroDigit;
};

} /* namespace alinous */

#endif /* NUMERIC_BIGINTEGER_H_ */
