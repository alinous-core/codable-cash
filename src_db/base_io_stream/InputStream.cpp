/*
 * InputStream.cpp
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "InputStream.h"

#include "base/ArrayList.h"

namespace alinous {

InputStream::InputStream() {
}

InputStream::~InputStream() {
}


int InputStream::read(char* b, int size) {
	return read(b, 0, size);
}

void InputStream::mark(int readlimit) {}
bool InputStream::markSupported() { return false; }
void InputStream::reset(){};



} /* namespace alinous */
