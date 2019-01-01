/*
 * Base58.h
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#ifndef BC_BASE_BASE58_H_
#define BC_BASE_BASE58_H_

namespace alinous {
class UnicodeString;
class ByteBuffer;
}

namespace codablecash {

using namespace alinous;

class Base58 {
public:
	static const constexpr char* ALPHABET{"123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"};
	static const constexpr char ENCODED_ZERO{1};
	static int* INDEXES;

	static UnicodeString* encode(const char* input, int inputLength) noexcept;
	static char* decode(UnicodeString* input) noexcept;

private:
	static char divmod(char* number, int numberLength, int firstDigit, int base, int divisor);
	static int* initIndex();
};

} /* namespace codablecash */

#endif /* BC_BASE_BASE58_H_ */
