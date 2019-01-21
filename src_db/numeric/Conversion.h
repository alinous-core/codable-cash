/*
 * Conversion.h
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#ifndef NUMERIC_CONVERSION_H_
#define NUMERIC_CONVERSION_H_

#include <inttypes.h>

namespace alinous {

class UnicodeString;

class BigInteger;

class Conversion {
public:
	static const constexpr int digitFitInInt[] { -1, -1, 31, 19, 15, 13, 11,
	            11, 10, 9, 9, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6,
	            6, 6, 6, 6, 6, 6, 6, 5 };

    static const constexpr int bigRadices[] { -2147483648, 1162261467,
            1073741824, 1220703125, 362797056, 1977326743, 1073741824,
            387420489, 1000000000, 214358881, 429981696, 815730721, 1475789056,
            170859375, 268435456, 410338673, 612220032, 893871739, 1280000000,
            1801088541, 113379904, 148035889, 191102976, 244140625, 308915776,
            387420489, 481890304, 594823321, 729000000, 887503681, 1073741824,
            1291467969, 1544804416, 1838265625, 60466176 };

    static UnicodeString* bigInteger2String(const BigInteger& val, int radix);
    static UnicodeString* toDecimalScaledString(BigInteger val, int scale);
    static int64_t divideLongByBillion(int64_t a);

    static void arraycopy(int* src, int srcPos, int* dest, int destPos, int length);
};

} /* namespace alinous */

#endif /* NUMERIC_CONVERSION_H_ */
