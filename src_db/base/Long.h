/*
 * Long.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef BASE_LONG_H_
#define BASE_LONG_H_

#include <cstdint>

namespace alinous {

class UnicodeString;

class Long {
public:
	Long();
	virtual ~Long();

	static int64_t parseLong(const UnicodeString* string);
	static int64_t parseLong(const UnicodeString* string, int radix);
	static int64_t parse(const UnicodeString* string, int offset, int radix, bool negative);

	static int numberOfLeadingZeros(int64_t lng);
	static int bitCount(int64_t lng);
	static UnicodeString* toString(int64_t l, int radix);
};

} /* namespace alinous */

#endif /* BASE_LONG_H_ */
