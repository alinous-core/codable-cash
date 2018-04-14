/*
 * ByteBuffer.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_IO_BYTEBUFFER_H_
#define BASE_IO_BYTEBUFFER_H_

#include <stdint.h>

namespace alinous {

template <typename T> class RawArrayPrimitive;

class ByteBuffer {
public:
	ByteBuffer() noexcept;
	ByteBuffer(int length) noexcept;
	virtual ~ByteBuffer();

private:
    int pos;
    int lim;
    int cap;
    RawArrayPrimitive<uint8_t>* buff;
};

} /* namespace alinous */

#endif /* BASE_IO_BYTEBUFFER_H_ */
