/*
 * CharsetManager.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include <charsets/CharsetManager.h>
#include "base/UnicodeString.h"

#include "CharsetConverter.h"
#include "charsets/UTF8.h"

#include "base/HashMap.h"
#include "base/StackRelease.h"


namespace alinous {

CharsetManager* CharsetManager::instance = nullptr;
const UnicodeString CharsetManager::UTF_8(L"utf_8");
const UnicodeString CharsetManager::_UTF_8(L"utf-8");

CharsetManager::CharsetManager() : charConverters(new HashMap<UnicodeString, CharsetConverter>()),
		__charConverters(new ArrayList<CharsetConverter>()){
}

CharsetManager::~CharsetManager() {
	int maxLoop = this->__charConverters->size();
	for(int i = 0; i != maxLoop; ++i){
		delete this->__charConverters->get(i);
	}

	delete this->__charConverters;
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
	UnicodeString* ucharset = charset->toLowerCase();
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

	if(ucharset->equals(&UTF_8) || altcharset->equals(&_UTF_8)){
		conv = new UTF_8Converter();
		this->charConverters->put(&UTF_8, conv);
		this->charConverters->put(&_UTF_8, conv);
		this->__charConverters->addElement(conv);

		return conv;
	}

	return nullptr;
}

} /* namespace alinous */
