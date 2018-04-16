/*
 * CharsetDecoder.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef CHARSETS_CHARSETDECODER_H_
#define CHARSETS_CHARSETDECODER_H_

#include "CoderResult.h"

namespace alinous {

class ByteBuffer;
class CharBuffer;

class CharsetDecoder {
public:
	CharsetDecoder();
	virtual ~CharsetDecoder();

	virtual CoderResult decodeLoop(ByteBuffer* bb, CharBuffer* cb) = 0;
};

} /* namespace alinous */

#endif /* CHARSETS_CHARSETDECODER_H_ */
