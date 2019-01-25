/*
 * CharBuffer.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base_io/CharBuffer.h"

#include "base/RawArrayPrimitive.h"
#include "base/UnicodeString.h"


namespace alinous {

CharBuffer::CharBuffer(const wchar_t* buffer, int length) noexcept {
	this->data = new RawArrayPrimitive<wchar_t>(length);
	this->data->setNumArray(length);

	this->lim = length;
	this->pos = 0;
	this->cap = length;

	const int maxLoop = length;
	for(int i = 0; i != maxLoop; ++i){
		data->set(i, buffer[i]);
	}
}

CharBuffer::CharBuffer(int size) noexcept {
	this->data = new RawArrayPrimitive<wchar_t>(size);
	this->data->setNumArray(size);

	this->lim = size;
	this->pos = 0;
	this->cap = size;
}

CharBuffer::~CharBuffer() noexcept {
	delete this->data;
}

CharBuffer* CharBuffer::wrap(const wchar_t* buffer, int begin, int count) noexcept {
	return new CharBuffer(buffer + begin, count);
}

CharBuffer* CharBuffer::wrap(const UnicodeString* str) noexcept {
	return wrap(str, 0, str->length());
}

CharBuffer* CharBuffer::wrap(const UnicodeString* str, int begin, int count) noexcept {
	CharBuffer* newBuffer = new CharBuffer(count);

	for (int i = 0; i < count; i++) {
		newBuffer->put(str->charAt(begin + i));
	}

	newBuffer->position(0);
	return newBuffer;
}

CharBuffer* CharBuffer::allocate(int capacity) noexcept {
	return new CharBuffer(capacity);
}

CharBuffer* CharBuffer::clear() noexcept {
	this->lim = this->cap;
	this->pos = 0;
	return this;
}

bool CharBuffer::hasRemaining() const noexcept {
    return (pos < lim);
}

int CharBuffer::remaining() const noexcept
{
	 return this->lim - this->pos;
}

int CharBuffer::position() const noexcept {
	return this->pos;
}

CharBuffer* CharBuffer::position(int newPosition) noexcept {
	this->pos = newPosition;
	return this;
}
int CharBuffer::limit() const noexcept {
	return this->lim;
}
CharBuffer* CharBuffer::limit(int limit) noexcept {
	this->lim = limit;
	return this;
}
int CharBuffer::capacity() const noexcept {
	return this->cap;
}
wchar_t CharBuffer::get() noexcept {
	return data->get(this->pos++);
}
wchar_t CharBuffer::get(int index) const noexcept {
	return data->get(index);
}
CharBuffer* CharBuffer::get(wchar_t* dest, int length) noexcept(false) {
	return get(dest, 0, length);
}
CharBuffer* CharBuffer::get(wchar_t* dest, int off, int length) noexcept(false) {

    /*if ((off < 0) || (length < 0) || ((off + length) > length) ) {
        throw new IndexOutOfBoundsException();
    }
*/
    if (length > remaining()) {
        throw new BufferUnderflowException(__FILE__, __LINE__);
    }

	int maxLoop = off + length;
    for (int i = off; i < maxLoop; i++) {
    	dest[i] = get();
    }
    return this;
}
CharBuffer* CharBuffer::put(wchar_t ch) noexcept{
	data->set(this->pos++, ch);
	return this;
}
CharBuffer* CharBuffer::put(int index, wchar_t ch) noexcept {
	data->set(index, ch);
	return this;
}
CharBuffer* CharBuffer::put(UnicodeString* str) noexcept {
	int maxLoop = str->length();
	for(int i = 0; i != maxLoop; ++i){
		data->set(this->pos++, str->charAt(i));
	}
	return this;
}
CharBuffer* CharBuffer::put(const wchar_t* src, int length) noexcept(false) {
	return put(src, 0, length);
}
CharBuffer* CharBuffer::put(const wchar_t* src, int off, int len) noexcept(false) {
    if (len > remaining()) {
        throw new BufferOverflowException(__FILE__, __LINE__);
    }
    for (int i = off; i < off + len; i++) {
        put(src[i]);
    }
    return this;
}

} /* namespace alinous */

