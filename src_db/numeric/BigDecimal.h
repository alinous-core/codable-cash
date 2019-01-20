/*
 * BigDecimal.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef NUMERIC_BIGDECIMAL_H_
#define NUMERIC_BIGDECIMAL_H_

#include <inttypes.h>

namespace alinous {

class UnicodeString;
class BigInteger;

class BigDecimal {
public:
	BigDecimal(UnicodeString* val);
	virtual ~BigDecimal();

private:
	void __BigDecimal(int16_t* in, int offset, int len);
	static int __bitLength(int64_t smallValue);
	void setUnscaledValue(BigInteger* unscaledValue);

private:
	int32_t scale;
	int64_t smallValue;
	int32_t bitLength;
	int32_t precision;
	BigInteger* intVal;

};

} /* namespace alinous */

#endif /* NUMERIC_BIGDECIMAL_H_ */
