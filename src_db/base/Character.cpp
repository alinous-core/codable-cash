/*
 * Character.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base/Character.h"
#include "unicode_icu/uchar.h"

namespace alinous {

Character::Character(wchar_t value) : value(value) {
}

Character::~Character() {
}

int Character::digit(int codePoint, int radix) noexcept {
	return icu::u_digit(codePoint, radix);
}

} /* namespace alinous */
