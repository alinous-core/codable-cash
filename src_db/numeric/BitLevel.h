/*
 * BitLevel.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef NUMERIC_BITLEVEL_H_
#define NUMERIC_BITLEVEL_H_

namespace alinous {

class BigInteger;

class BitLevel {
public:
	BitLevel();
	virtual ~BitLevel();

	static int bitLength(BigInteger* val);
};

} /* namespace alinous */

#endif /* NUMERIC_BITLEVEL_H_ */
