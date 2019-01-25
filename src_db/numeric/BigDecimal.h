/*
 * BigDecimal.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef NUMERIC_BIGDECIMAL_H_
#define NUMERIC_BIGDECIMAL_H_

#include <cstdint>

namespace alinous {

class UnicodeString;
class BigInteger;

class BigDecimal {
public:
	explicit BigDecimal(UnicodeString* val);
	virtual ~BigDecimal();

	int64_t longValue();
	BigInteger toBigInteger();
private:
	static const constexpr double LOG10_2 = 0.3010299956639812;

	void __BigDecimal(int16_t* in, int offset, int len);
	static int __bitLength(int64_t smallValue);
	void setUnscaledValue(const BigInteger& unscaledValue);
	BigInteger getUnscaledValue();
	bool isZero() const;
	int aproxPrecision() const;



private:
	int32_t scale;
	int64_t smallValue;
	int32_t bitLength;
	int32_t precision;
	BigInteger* intVal;

};

} /* namespace alinous */

#endif /* NUMERIC_BIGDECIMAL_H_ */
