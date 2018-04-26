/*
 * OutputStream.h
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_OUTPUTSTREAM_H_
#define BASE_IO_STREAM_OUTPUTSTREAM_H_

#include "base/RawArrayPrimitive.h"

namespace alinous {

class OutputStream {
public:
	OutputStream();
	virtual ~OutputStream();

	virtual void close() = 0;
	virtual void flush() = 0;
	virtual void write(const char* buffer, int size);
	virtual void write(const char* buffer, int off, int len) = 0;

};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_OUTPUTSTREAM_H_ */
