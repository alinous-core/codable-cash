/*
 * InputStream.h
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_INPUTSTREAM_H_
#define BASE_IO_STREAM_INPUTSTREAM_H_

#include <stdint.h>

#include "base/ArrayList.h"

namespace alinous {


class InputStream {
public:
	InputStream();
	virtual ~InputStream();

	virtual void close() = 0;
	virtual int read(const ArrayList<char>* b, int off, int len) = 0;
	virtual int read(const ArrayList<char>* b);
	virtual int read() = 0;
	virtual int available();
	virtual void mark(int readlimit);
	virtual bool markSupported();
	virtual void reset();

	virtual int64_t skip(int64_t n);
};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_INPUTSTREAM_H_ */
