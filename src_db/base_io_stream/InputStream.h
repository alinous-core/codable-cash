/*
 * InputStream.h
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_INPUTSTREAM_H_
#define BASE_IO_STREAM_INPUTSTREAM_H_

#include <stdint.h>

#include "base/RawArrayPrimitive.h"

namespace alinous {


class InputStream {
public:
	InputStream();
	virtual ~InputStream();

	virtual void open() = 0;
	virtual void close() = 0;
	virtual int read(char* b, int off, int len) = 0;
	virtual int read(char* b, int size);
	virtual int available() = 0;
	virtual void mark(int readlimit);
	virtual bool markSupported();
	virtual void reset();

};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_INPUTSTREAM_H_ */
