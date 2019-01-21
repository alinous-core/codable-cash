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
	static BigInteger* shiftLeft(BigInteger* source, int count);
	static BigInteger* shiftRight(BigInteger* source, int count);


	static void arraycopy(int* src, int srcPos, int* dest, int destPos, int length);

	static void shiftLeft(int* result, int result_len, int* source, int intCount, int count);
	static bool shiftRight(int* result, int resultLen, int* source, int intCount, int count);

	static void shiftLeftOneBit(int* result, int* source, int srcLen);
};

} /* namespace alinous */

#endif /* NUMERIC_BITLEVEL_H_ */
