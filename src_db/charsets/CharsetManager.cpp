/*
 * CharsetManager.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include <charsets/CharsetManager.h>
#include "base/UnicodeString.h"

#include "CharsetConverter.h"
#include "base/HashMap.h"

namespace alinous {

CharsetManager::CharsetManager() {
}

CharsetManager::~CharsetManager() {
}

CharsetConverter* CharsetManager::getConverter(UnicodeString* charset) noexcept {
	return nullptr;
}

} /* namespace alinous */
