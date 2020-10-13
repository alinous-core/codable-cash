/*
 * ParserReaderStream.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "engine/compiler/ParserReaderStream.h"
#include "base_io_stream/InputStream.h"

namespace alinous {

ParserReaderStream::ParserReaderStream(InputStream* inputStream, int size) {
	this->inputStream = inputStream;
	this->cur_ = 0;
	this->max_ = size;
}

ParserReaderStream::~ParserReaderStream() {
	this->inputStream->close();
}

size_t ParserReaderStream::read(char* buffer, int offset, size_t len) {
	size_t count = this->inputStream->read(buffer, offset, len);//str_.copy(bufptr + offset, len > max_ ? max_ : len, cur_);
	cur_ += count;
	max_ -= count;

	return count;
}

bool ParserReaderStream::endOfInput() {
	return max_ == 0;
}

} /* namespace alinous */
