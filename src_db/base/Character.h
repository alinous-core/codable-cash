/*
 * Character.h
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#ifndef BASE_CHARACTER_H_
#define BASE_CHARACTER_H_

namespace alinous {

class Character {
public:
	static const constexpr int MIN_RADIX = 2;
	static const constexpr int MAX_RADIX = 36;

	explicit Character(wchar_t value);
	virtual ~Character();

	static int digit(int codePoint, int radix) noexcept;
	static wchar_t forDigit(int digit, int radix);
private:
	wchar_t value;

};

} /* namespace alinous */

#endif /* BASE_CHARACTER_H_ */
