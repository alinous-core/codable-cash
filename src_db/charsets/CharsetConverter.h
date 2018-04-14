/*
 * CharsetConverter.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef CHARSETS_CHARSETCONVERTER_H_
#define CHARSETS_CHARSETCONVERTER_H_

namespace alinous {

class CharsetDecoder;
class CharsetEncoder;

class CharsetConverter {
public:
	CharsetConverter();
	virtual ~CharsetConverter();

	virtual CharsetDecoder* newDecoder() noexcept  = 0;
	virtual CharsetEncoder* newEncoder() noexcept  = 0;
};

} /* namespace alinous */

#endif /* CHARSETS_CHARSETCONVERTER_H_ */
