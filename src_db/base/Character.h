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
	explicit Character(wchar_t value);
	virtual ~Character();

	static int digit(int codePoint, int radix) noexcept;
private:
	wchar_t value;

};

} /* namespace alinous */

#endif /* BASE_CHARACTER_H_ */
