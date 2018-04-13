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

class CharsetManager {
public:
	CharsetManager();
	virtual ~CharsetManager();

	CharsetConverter* getConverter(UnicodeString* charset) throw();
};

} /* namespace alinous */

#endif /* CHARSETS_CHARSETMANAGER_H_ */
