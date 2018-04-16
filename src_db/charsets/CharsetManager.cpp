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
#include "base/StackRelease.h"

namespace alinous {

CharsetManager* CharsetManager::instance = nullptr;

CharsetManager::CharsetManager() : charConverters(new HashMap<UnicodeString, CharsetConverter>()) {
}

CharsetManager::~CharsetManager() {
	delete this->charConverters;
}

CharsetManager* CharsetManager::getInstance() noexcept {
	if(CharsetManager::instance == nullptr)
	{
		CharsetManager::instance = new CharsetManager();
	}
	return CharsetManager::instance;
}
void CharsetManager::closeInstance() noexcept {
	if(CharsetManager::instance != nullptr){
		delete CharsetManager::instance;
		CharsetManager::instance = nullptr;
	}
}

CharsetConverter* CharsetManager::getConverter(UnicodeString* charset) noexcept {
	UnicodeString* ucharset = charset->toUpperCase();
	StackRelease<UnicodeString> r_ucharset(ucharset);

	UnicodeString* altcharset = ucharset->replace(L'-', L'_');
	StackRelease<UnicodeString> r_altcharset(altcharset);

	CharsetConverter* conv = this->charConverters->get(ucharset);
	if(conv != nullptr)
	{
		return conv;
		conv = this->charConverters->get(altcharset);
		if(conv != nullptr)
		{
			return conv;
		}
	}

	return nullptr;
}

} /* namespace alinous */
