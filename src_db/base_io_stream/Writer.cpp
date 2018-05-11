/*
 * Writer.cpp
 *
 *  Created on: 2018/05/10
 *      Author: iizuka
 */

#include "base_io_stream/Writer.h"
#include "base/UnicodeString.h"

namespace alinous {

Writer::~Writer() {
}

Writer::Writer() {
}


void Writer::write(const wchar_t* cbuf) {
	int size = Mem::wstrlen(cbuf);
	write(cbuf, size);
}
void Writer::write(const wchar_t* cbuf, int size) {
	write(cbuf, 0, size);
}

void Writer::write(const UnicodeString* str) {
	write(str, 0, str->length());
}

} /* namespace alinous */
