/*
 * CharsetManager.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef CHARSETS_CHARSETMANAGER_H_
#define CHARSETS_CHARSETMANAGER_H_

#include "base/UnicodeString.h"
#include "base/ArrayList.h"

#include "CharsetConverter.h"
#include "charsets/UTF8.h"

namespace alinous {

class CharsetConverter;
template<typename K, typename V> class HashMap;

class CharsetManager {
private:
	CharsetManager(const CharsetManager& base) = delete;
	CharsetManager();
public:
	virtual ~CharsetManager();

	static CharsetManager* getInstance() noexcept;
	static void closeInstance() noexcept;


	static const UnicodeString* UTF_8() noexcept;
	static const UnicodeString* _UTF_8() noexcept;

	CharsetConverter* getConverter(const UnicodeString* charset) noexcept;
private:
	static CharsetManager* instance;
	HashMap<UnicodeString, CharsetConverter>* charConverters;
	ArrayList<CharsetConverter>* __charConverters;
};

} /* namespace alinous */

#endif /* CHARSETS_CHARSETMANAGER_H_ */
