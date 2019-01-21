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

char Character::forDigit(int digit, int radix) {
    if (MIN_RADIX <= radix && radix <= MAX_RADIX) {
        if (0 <= digit && digit < radix) {
            return (char) (digit < 10 ? digit + '0' : digit + 'a' - 10);
        }
    }
    return 0;
}

} /* namespace alinous */
