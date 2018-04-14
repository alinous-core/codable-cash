/*
 * CharBuffer.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include <base_io/CharBuffer.h>

#include "base/RawArrayPrimitive.h"
#include "base/UnicodeString.h"


namespace alinous {

CharBuffer::CharBuffer(int size) throw() {
	this->data = new RawArrayPrimitive<wchar_t>(size);
	this->data->setNumArray(size);

	this->lim = size;
	this->pos = 0;
	this->cap = size;
}

CharBuffer::~CharBuffer() throw() {
	delete this->data;
}


CharBuffer* CharBuffer::allocate(int capacity) throw() {
	return new CharBuffer(capacity);
}

CharBuffer* CharBuffer::clear() throw() {
	this->lim = this->cap;
	this->pos = 0;
	return this;
}

bool CharBuffer::hasRemaining() const throw() {
    return (pos < lim);
}

int CharBuffer::remaining() const throw()
{
	 return this->lim - this->pos;
}

CharBuffer* CharBuffer::position(int newPosition) throw() {
	this->pos = newPosition;
	return this;
}
int CharBuffer::limit() const throw() {
	return this->lim;
}
CharBuffer* CharBuffer::limit(int limit) throw() {
	this->lim = limit;
	return this;
}
wchar_t CharBuffer::get() throw() {
	return data->get(this->pos++);
}
wchar_t CharBuffer::get(int index) const throw() {
	return data->get(index);
}
CharBuffer* CharBuffer::get(wchar_t* dest, int length) throw(BufferUnderflowException) {
	return get(dest, 0, length);
}
CharBuffer* CharBuffer::get(wchar_t* dest, int off, int length) throw(BufferUnderflowException) {
    /*if ((off < 0) || (length < 0) || ((off + length) > length) ) {
        throw new IndexOutOfBoundsException();
    }
*/
    if (length > remaining()) {
        throw new BufferUnderflowException();
    }

	int maxLoop = off + length;
    for (int i = off; i < maxLoop; i++) {
    	dest[i] = get();
    }
    return this;
}
CharBuffer* CharBuffer::put(wchar_t ch) throw(){

}
CharBuffer* CharBuffer::put(int index, wchar_t ch) throw() {

}
CharBuffer* CharBuffer::put(UnicodeString* str) throw() {

}
CharBuffer* CharBuffer::put(wchar_t* src) throw() {

}
CharBuffer* CharBuffer::put(wchar_t* src, int off, int len) throw() {

}

} /* namespace alinous */
