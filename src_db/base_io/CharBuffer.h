/*
 * CharBuffer.h
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#ifndef BASE_IO_CHARBUFFER_H_
#define BASE_IO_CHARBUFFER_H_

#include "base_io/exceptions.h"

namespace alinous {

template<typename T>
class RawArrayPrimitive;
class UnicodeString;
class BufferUnderflowException;

class CharBuffer {
protected:
	CharBuffer(int size) noexcept;
public:
	virtual ~CharBuffer() noexcept;

	static CharBuffer* allocate(int capacity) noexcept;

	CharBuffer* clear() noexcept;
	bool hasRemaining() const noexcept;
	int remaining() const noexcept;
	CharBuffer* position(int newPosition) noexcept;
	int limit() const noexcept;
	CharBuffer* limit(int limit) noexcept;
	wchar_t get() noexcept;
	wchar_t get(int index) const noexcept;
	CharBuffer* get(wchar_t* dest, int length) noexcept(false);
	CharBuffer* get(wchar_t* dest, int off, int len) noexcept(false);
	CharBuffer* put(wchar_t ch) noexcept;
	CharBuffer* put(int index, wchar_t ch) noexcept;
	CharBuffer* put(UnicodeString* str) noexcept;
	CharBuffer* put(wchar_t* src) noexcept;
	CharBuffer* put(wchar_t* src, int off, int len) noexcept;
private:
    int pos;
    int lim;
    int cap;
    RawArrayPrimitive<wchar_t>* data;
};

} /* namespace alinous */

#endif /* BASE_IO_CHARBUFFER_H_ */
