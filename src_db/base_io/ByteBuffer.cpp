/*
 * ByteBuffer.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include <base_io/ByteBuffer.h>
#include "base/RawArrayPrimitive.h"

namespace alinous {

ByteBuffer::ByteBuffer() noexcept {
	this->buff = new RawArrayPrimitive<uint8_t>(64);
	this->lim = 64;
	this->cap = 64;
	this->pos = 0;
}

ByteBuffer::ByteBuffer(int length) noexcept {
	this->buff = new RawArrayPrimitive<uint8_t>(length);
	this->lim = length;
	this->cap = length;
	this->pos = 0;
}

ByteBuffer::~ByteBuffer() {
	delete this->buff;
}

} /* namespace alinous */
