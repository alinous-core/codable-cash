/*
 * OutputStream.cpp
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#include "OutputStream.h"

namespace alinous {

OutputStream::OutputStream() {
}

OutputStream::~OutputStream() {
}

void OutputStream::write(const RawArrayPrimitive<char>* buffer) {
    write(buffer, 0, buffer->size());
}

bool OutputStream::checkError(){
	return false;
}

} /* namespace alinous */
