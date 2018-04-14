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
	CharBuffer(int size) throw();
public:
	virtual ~CharBuffer() throw();

	static CharBuffer* allocate(int capacity) throw();

	CharBuffer* clear() throw();
	bool hasRemaining() const throw();
	int remaining() const throw();
	CharBuffer* position(int newPosition) throw();
	int limit() const throw();
	CharBuffer* limit(int limit) throw();
	wchar_t get() throw();
	wchar_t get(int index) const throw();
	CharBuffer* get(wchar_t* dest, int length) throw(BufferUnderflowException);
	CharBuffer* get(wchar_t* dest, int off, int len) throw(BufferUnderflowException);
	CharBuffer* put(wchar_t ch) throw();
	CharBuffer* put(int index, wchar_t ch) throw();
	CharBuffer* put(UnicodeString* str) throw();
	CharBuffer* put(wchar_t* src) throw();
	CharBuffer* put(wchar_t* src, int off, int len) throw();
private:
    int pos;
    int lim;
    int cap;
    RawArrayPrimitive<wchar_t>* data;
};

} /* namespace alinous */

#endif /* BASE_IO_CHARBUFFER_H_ */
