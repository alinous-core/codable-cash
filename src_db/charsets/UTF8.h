/*
 * UTF8.h
 *
 *  Created on: 2018/04/16
 *      Author: iizuka
 */

#ifndef CHARSETS_UTF8_H_
#define CHARSETS_UTF8_H_

#include "CharsetConverter.h"
#include "CharsetDecoder.h"
#include "CharsetEncoder.h"

namespace alinous {

class UnicodeString;

class UTF_8 : public CharsetConverter {
public:
	class Decoder;
	class Encoder;

	UTF_8();
	virtual ~UTF_8();

	virtual CharsetDecoder* newDecoder() noexcept {
		return &decoder;
	}
	virtual CharsetEncoder* newEncoder() noexcept {
		return &encoder;
	}


	class Decoder final : public CharsetDecoder {
	public:
		Decoder() throw() ;
		virtual ~Decoder() throw();
	private:
		static constexpr int remainingBytes[]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, -1, -1, -1, -1, -1, -1, -1, -1};
		static constexpr int remainingNumbers[]{0, 4224, 401536, 29892736};
		static constexpr int lowerEncodingLimit[]{-1, 0x80, 0x800, 0x10000};

	public:
		virtual CoderResult decodeLoop(ByteBuffer* in, CharBuffer* out) final;
	};

	class Encoder final : public CharsetEncoder {
	public:
		Encoder(const Encoder& base) = default;
	public:
		Encoder() noexcept;
		virtual ~Encoder() noexcept;
	public:
		virtual CoderResult encodeLoop(CharBuffer* in, ByteBuffer* out) final;
	};

	private:
	Decoder decoder;
	Encoder encoder;

};

} /* namespace alinous */

#endif /* CHARSETS_UTF8_H_ */
