/*
 * CharsetManager.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef CHARSETS_CHARSETMANAGER_H_
#define CHARSETS_CHARSETMANAGER_H_

namespace alinous {

class UnicodeString;
class CharsetConverter;
template<typename K, typename V> class HashMap;

class CharsetManager {
private:
	CharsetManager();
public:
	virtual ~CharsetManager();

	static CharsetManager* getInstance() noexcept;
	static void closeInstance() noexcept;

	CharsetConverter* getConverter(UnicodeString* charset) noexcept;
private:
	static CharsetManager* instance;
	HashMap<UnicodeString, CharsetConverter>* charConverters;
};

} /* namespace alinous */

#endif /* CHARSETS_CHARSETMANAGER_H_ */
