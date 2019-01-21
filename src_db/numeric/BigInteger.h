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
class Conversion;

class BigInteger {
	friend class BitLevel;
	friend class Multiplication;
	friend class Elementary;
	friend class Conversion;
public:
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

    BigInteger() = delete;
	BigInteger(const BigInteger& inst);
	BigInteger &operator=(const BigInteger &inst){
		this->firstNonzeroDigit = inst.firstNonzeroDigit;
		this->sign = inst.sign;
		this->numberLength = inst.numberLength;

		if(this->digits){
			delete [] this->digits;
		}
		this->digits = new int[this->numberLength] {};

		for(int i = 0; i != this->numberLength; ++i){
			this->digits[i] = inst.digits[i];
		}

		return(*this);
	}

	BigInteger(int sign, int value);
	BigInteger(int sign, int numberLength, const int* digits);

	explicit BigInteger(const UnicodeString* val);
	BigInteger(const UnicodeString* val, int radix);
	virtual ~BigInteger();

	int bitLength() const;

	int64_t longValue() const;

	BigInteger multiply(const BigInteger& val) const;
	BigInteger shiftRight(int n) const;
	BigInteger shiftLeft(int n);
	BigInteger subtract(const BigInteger& val) const;
	BigInteger add(BigInteger& val);
	BigInteger divide(BigInteger& divisor);

	BigInteger pow(int exp);

	BigInteger abs() const;
	BigInteger negate() const;
	bool isOne();
	bool testBit(int n);
	int getFirstNonzeroDigit() const;

	static BigInteger valueOf(int64_t val);

	bool equals(const BigInteger* x) const;
	bool equalsArrays(const int* b) const;

    static BigInteger getPowerOfTwo(int exp);

    UnicodeString* toString(int radix);
    UnicodeString* toString() const;

    static void test(){};
private:
	static void setFromString(BigInteger* bi, const UnicodeString* val, int radix);
	void cutOffLeadingZeroes();

private:
	int numberLength;
	int sign;
	int* digits;
	mutable int firstNonzeroDigit;
};

} /* namespace alinous */

#endif /* NUMERIC_BIGINTEGER_H_ */
