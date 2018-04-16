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

namespace alinous {

class CharsetConverter;
template<typename K, typename V> class HashMap;

class CharsetManager {
private:
	CharsetManager();
public:
	virtual ~CharsetManager();

	static CharsetManager* getInstance() noexcept;
	static void closeInstance() noexcept;

	static const UnicodeString UTF_8;
	static const UnicodeString _UTF_8;

	CharsetConverter* getConverter(UnicodeString* charset) noexcept;
private:
	static CharsetManager* instance;
	HashMap<UnicodeString, CharsetConverter>* charConverters;
	ArrayList<CharsetConverter>* __charConverters;
};

} /* namespace alinous */

#endif /* CHARSETS_CHARSETMANAGER_H_ */
