/*
 * BigInteger.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef NUMERIC_BIGINTEGER_H_
#define NUMERIC_BIGINTEGER_H_

#include <inttypes.h>
#include <gmp.h>

namespace alinous {

class UnicodeString;
class ByteBuffer;

class BigInteger {
private:
	explicit BigInteger(const mpz_t mpvalue);
public:
    BigInteger() = delete;
	BigInteger(const BigInteger& inst);
	BigInteger &operator=(const BigInteger &inst){
		mpz_set(this->value, inst.value);

		return(*this);
	}

	explicit BigInteger(const wchar_t* str, int radix);
	explicit BigInteger(int64_t value);
	explicit BigInteger(const UnicodeString* val);
	BigInteger(const UnicodeString* val, int radix);
	virtual ~BigInteger();

	int bitLength() const;

	int64_t longValue() const;

	BigInteger multiply(const BigInteger& val) const;
	BigInteger subtract(const BigInteger& val) const;
	BigInteger add(const BigInteger& val) const;
	BigInteger divide(const BigInteger& divisor) const;

	BigInteger rightShift(int n) const;
	BigInteger shiftLeft(int n) const;

	BigInteger pow(uint64_t exp) const;

	BigInteger abs() const;
	BigInteger negate() const;
	bool testBit(int n) const;

	static BigInteger valueOf(int64_t val);

	bool equals(const BigInteger* x) const;

    UnicodeString* toString(int radix) const;
    UnicodeString* toString() const;

    ByteBuffer* toBinary() const;
	static BigInteger* fromBinary(const char* buff, int length);

private:
	mpz_t value;
};

} /* namespace alinous */

#endif /* NUMERIC_BIGINTEGER_H_ */
