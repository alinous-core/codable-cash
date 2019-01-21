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
class Multiplication;
class Elementary;

class BigInteger {
public:
	friend class BitLevel;
	friend class Multiplication;
	friend class Elementary;

    static const constexpr int EQUALS = 0;
    static const constexpr int GREATER = 1;
    static const constexpr int LESS = -1;

    static const BigInteger ZERO;
    static const BigInteger ONE;
    static BigInteger TEN;

    static const BigInteger* SMALL_VALUE;
    static BigInteger* __SMALL_VALUES();

    static BigInteger** TWO_POWS;
    static BigInteger** initTwoPows();

	BigInteger(const BigInteger& inst);

	BigInteger(int sign, int value);
	BigInteger(int sign, int numberLength, int* digits);

	explicit BigInteger(UnicodeString* val);
	BigInteger(UnicodeString* val, int radix);
	virtual ~BigInteger();

	int bitLength();

	int64_t longValue();

	BigInteger* multiply(const BigInteger* val) const;
	BigInteger* shiftRight(int n) const;
	BigInteger* shiftLeft(int n);
	BigInteger* subtract(BigInteger* val) const;
	BigInteger* add(BigInteger* val);
	BigInteger* divide(BigInteger* divisor);

	BigInteger* pow(int exp);

	BigInteger* negate() const;
	bool isOne();
	bool testBit(int n);
	int getFirstNonzeroDigit();

	static BigInteger* valueOf(int64_t val);

	bool equals(const BigInteger* x) const;
	bool equalsArrays(const int* b) const;

    static BigInteger* getPowerOfTwo(int exp);

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
