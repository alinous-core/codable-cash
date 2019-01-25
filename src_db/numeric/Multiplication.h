/*
 * Multiplication.h
 *
 *  Created on: 2019/01/22
 *      Author: iizuka
 */

#ifndef NUMERIC_MULTIPLICATION_H_
#define NUMERIC_MULTIPLICATION_H_

#include <cstdint>

namespace alinous {

class BigInteger;

class Multiplication {
public:
	static const BigInteger** bigTenPows;
	static const BigInteger** bigFivePows;

	static const BigInteger** initbigpows(bool ten);

	static BigInteger powerOf10(int64_t exp);
};

} /* namespace alinous */

#endif /* NUMERIC_MULTIPLICATION_H_ */
