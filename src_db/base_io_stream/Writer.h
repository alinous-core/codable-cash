/*
 * Writer.h
 *
 *  Created on: 2018/05/10
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_WRITER_H_
#define BASE_IO_STREAM_WRITER_H_

namespace alinous {

class UnicodeString;

class Writer {
public:
	virtual ~Writer();
	Writer();

	virtual void close() = 0;
	virtual void flush() = 0;

	virtual void write(wchar_t* cbuf, int size);
	virtual void write(wchar_t* cbuf, int off, int len) = 0;

	virtual void write(UnicodeString* str);
	virtual void write(UnicodeString* str, int off, int len) = 0;
};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_WRITER_H_ */
