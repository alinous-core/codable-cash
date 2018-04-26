/*
 * OutputStream.cpp
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "OutputStream.h"

namespace alinous {

OutputStream::OutputStream() {
}

OutputStream::~OutputStream() {
}

void OutputStream::write(const char* buffer, int size) {
    write(buffer, 0, size);
}


} /* namespace alinous */
