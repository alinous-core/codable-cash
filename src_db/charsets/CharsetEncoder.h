/*
 * CharsetEncoder.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef CHARSETS_CHARSETENCODER_H_
#define CHARSETS_CHARSETENCODER_H_

#include "CoderResult.h"

namespace alinous {

class CharBuffer;
class ByteBuffer;

class CharsetEncoder {
public:
	CharsetEncoder();
	virtual ~CharsetEncoder();

	virtual CoderResult encodeLoop(CharBuffer* in, ByteBuffer* out) = 0;
};

} /* namespace alinous */

#endif /* CHARSETS_CHARSETENCODER_H_ */
