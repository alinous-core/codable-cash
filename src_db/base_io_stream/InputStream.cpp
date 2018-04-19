/*
 * InputStream.cpp
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#include "InputStream.h"

#include "base/ArrayList.h"

namespace alinous {

InputStream::InputStream() {
}

InputStream::~InputStream() {
}


int InputStream::read(const ArrayList<char>* b) {
	return read(b, 0, b->size());
}

int InputStream::available() { return 0; }
void InputStream::mark(int readlimit) {}
bool InputStream::markSupported() { return false; }
void InputStream::reset(){};
int64_t InputStream::skip(int64_t n){ return n; }






} /* namespace alinous */
