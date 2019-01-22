/*
 * BigInteger.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "numeric/BigInteger.h"
#include "numeric/exceptions.h"

#include "base/UnicodeString.h"
#include "base/Integer.h"

#include "base/StackRelease.h"
#include "base/ArrayList.h"

#include <stdlib.h>


namespace alinous {

BigInteger::BigInteger(const mpz_t mpvalue) {
	mpz_init_set(this->value, mpvalue);
}


BigInteger::BigInteger(const BigInteger& inst) {
	mpz_init(this->value);
	mpz_set(this->value, inst.value);
}

BigInteger::BigInteger(int64_t value) {
	mpz_init(this->value);
	mpz_set_si(this->value, value);
}

BigInteger::BigInteger(const UnicodeString* val, int radix) {
	const char* str = val->toCString();

	mpz_init_set_str(this->value, str, radix);

	delete [] str;
}

BigInteger::BigInteger(const UnicodeString* val) {
	const char* str = val->toCString();

	mpz_init_set_str(this->value, str, 10);

	delete [] str;
}

BigInteger::~BigInteger() {
	mpz_clear(this->value);
}

int BigInteger::bitLength() const {
	return mpz_sizeinbase(this->value, 2);
}

int64_t BigInteger::longValue() const {
	return mpz_get_si(this->value);
}

BigInteger BigInteger::multiply(const BigInteger& val) const {
	mpz_t op;
	mpz_init(op);

	mpz_mul(op, this->value, val.value);

	return BigInteger(op);
}

BigInteger BigInteger::subtract(const BigInteger& val) const {
	mpz_t op;
	mpz_init(op);

	mpz_sub(op, this->value, val.value);

	return BigInteger(op);
}

BigInteger BigInteger::add(const BigInteger& val) {
	mpz_t op;
	mpz_init(op);

	mpz_add(op, this->value, val.value);

	return BigInteger(op);
}

BigInteger BigInteger::divide(const BigInteger& divisor) {
	mpz_t op;
	mpz_init(op);

	mpz_tdiv_q(op, this->value, divisor.value);

	return BigInteger(op);
}

BigInteger BigInteger::pow(uint64_t exp) {
	mpz_t op;
	mpz_init(op);

	mpz_pow_ui(op, this->value, exp);


	return BigInteger(op);
}

BigInteger BigInteger::shiftLeft(int n) {
	int sign = mpz_sgn(this->value);

    if ((n == 0) || (sign == 0)) {
        return *this;
    }
    if(n < 0){
    	return rightShift(-n);
    }

	mpz_t op;
	mpz_init(op);
    mpz_mul_2exp(op, this->value, n);

    return BigInteger(op);
}

BigInteger BigInteger::rightShift(int n) {
	int sign = mpz_sgn(this->value);

    if ((n == 0) || (sign == 0)) {
        return *this;
    }
    if(n < 0){
    	return shiftLeft(-n);
    }

	mpz_t op;
	mpz_init(op);
	mpz_tdiv_q_2exp(op, this->value, n);

    return BigInteger(op);
}


bool BigInteger::equals(const BigInteger* x1) const {
	int cmp = mpz_cmp(this->value, x1->value);
	return cmp == 0;
}

bool BigInteger::testBit(int n) {
	mp_bitcnt_t bit_index = n;
	return mpz_tstbit(this->value, bit_index);
}

UnicodeString* BigInteger::toString(int radix) const {
	size_t count;
	char *buff = mpz_get_str(nullptr, radix, this->value);

	UnicodeString* str = new UnicodeString(buff);

	::free(buff);

	return str;
}

UnicodeString* BigInteger::toString() const {
	return toString(10);
}

BigInteger BigInteger::abs() const {
	mpz_t op;
	mpz_init(op);

	mpz_abs(op, this->value);

	return BigInteger(op);
}

BigInteger BigInteger::negate() const {
	mpz_t op;
	mpz_init(op);

	mpz_neg(op, this->value);

	return BigInteger(op);
}

BigInteger BigInteger::valueOf(int64_t val) {
	return BigInteger(val);
}

} /* namespace alinous */


