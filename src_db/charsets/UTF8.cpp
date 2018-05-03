/*
 * UTF8.cpp
 *
 *  Created on: 2018/04/16
 *      Author: iizuka
 */

#include "debug/debugMacros.h"
#include "charsets/UTF8.h"

#include "base_io/CharBuffer.h"
#include "base_io/ByteBuffer.h"

namespace alinous {

constexpr int UTF_8Converter::Decoder::remainingBytes[];
constexpr int UTF_8Converter::Decoder::remainingNumbers[];
constexpr int UTF_8Converter::Decoder::lowerEncodingLimit[];

UTF_8Converter::UTF_8Converter() noexcept : CharsetConverter() {
}

UTF_8Converter::~UTF_8Converter() noexcept {
}

UTF_8Converter::Decoder::Decoder() noexcept : CharsetDecoder() {

}
UTF_8Converter::Decoder::~Decoder() {
}

UTF_8Converter::Encoder::Encoder() noexcept : CharsetEncoder() {
}
UTF_8Converter::Encoder::~Encoder() noexcept{
}

CoderResult UTF_8Converter::Decoder::decodeLoop(ByteBuffer* in, CharBuffer* out) {
	int outRemaining = out->remaining();
	int pos = in->position();
	int limit = in->limit();
	{
		try
		{
			int nextByte = 0;
			while(pos < limit)
			{
				if(outRemaining == 0)
				{
					in->position(pos);
					return CoderResult::__OVERFLOW;
				}
				int jchar = in->get();
				if(jchar < 0)
				{
					jchar = jchar & 0x7F;
					int tail = remainingBytes[jchar];
					if(tail == -1)
					{
						in->position(pos);
						return CoderResult::malformedForLength(1);
					}
					if(limit - pos < 1 + tail)
					{
						in->position(pos);
						return CoderResult::__UNDERFLOW;
					}
					nextByte = 0;
					for(int i = 0; i < tail; i ++ )
					{
						nextByte = in->get() & 0xFF;
						if((nextByte & 0xC0) != 0x80)
						{
							in->position(pos);
							return CoderResult::malformedForLength(1 + i);
						}
						jchar = (jchar << 6) + nextByte;
					}
					jchar -= remainingNumbers[tail];
					if(jchar < lowerEncodingLimit[tail])
					{
						in->position(pos);
						return CoderResult::malformedForLength(1);
					}
					pos += tail;
				}
				if(jchar <= 0xffff)
				{
					out->put(((wchar_t)jchar));
					outRemaining -- ;
				}
				else{
					if(outRemaining < 2)
					{
						in->position(pos);
						return CoderResult::__OVERFLOW;
					}
					out->put(((wchar_t)((jchar >> 0xA) + 0xD7C0)));
					out->put(((wchar_t)((jchar & 0x3FF) + 0xDC00)));
					outRemaining -= 2;
				}
				pos ++ ;
			}
			in->position(pos);
			return CoderResult::__UNDERFLOW;
		}
		catch(Exception* e)
		{
			in->position(pos);
			throw e;
		}
	}
}

CoderResult UTF_8Converter::Encoder::encodeLoop(CharBuffer* in, ByteBuffer* out) {
	int outRemaining = out->remaining();
	int pos = in->position();
	int limit = in->limit();
	{
		try
		{
			while(pos < limit)
			{
				if(outRemaining == 0)
				{
					in->position(pos);
					return CoderResult::__OVERFLOW;
				}
				int jchar = (in->get() & 0xFFFF);
				if(jchar <= 0x7F)
				{
					if(outRemaining < 1)
					{
						in->position(pos);
						return CoderResult::__OVERFLOW;
					}
					out->put(((char)(jchar & 0xFF)));
					outRemaining -- ;
				}
				else {
					if(jchar <= 0x7FF)
					{
						if(outRemaining < 2)
						{
							in->position(pos);
							return CoderResult::__OVERFLOW;
						}
						out->put(((char)(0xC0 + ((jchar >> 6) & 0x1F))));
						out->put(((char)(0x80 + (jchar & 0x3F))));
						outRemaining -= 2;
					}
					else {
						if(jchar >= 0xD800 && jchar <= 0xDFFF)
						{
							if(limit <= pos + 1)
							{
								in->position(pos);
								return CoderResult::__UNDERFLOW;
							}
							if(outRemaining < 4)
							{
								in->position(pos);
								return CoderResult::__OVERFLOW;
							}
							if(jchar >= 0xDC00)
							{
								in->position(pos);
								return CoderResult::malformedForLength(1);
							}
							int jchar2 = (in->get() & 0xFFFF);
							if(jchar2 < 0xDC00)
							{
								in->position(pos);
								return CoderResult::malformedForLength(1);
							}
							int n = (jchar << 10) + jchar2 + 0xFCA02400;
							out->put(((char)(0xF0 + ((n >> 18) & 0x07))));
							out->put(((char)(0x80 + ((n >> 12) & 0x3F))));
							out->put(((char)(0x80 + ((n >> 6) & 0x3F))));
							out->put(((char)(0x80 + (n & 0x3F))));
							outRemaining -= 4;
							pos ++ ;
						}
						else {
							if(outRemaining < 3)
							{
								in->position(pos);
								return CoderResult::__OVERFLOW;
							}
							out->put(((char)(0xE0 + ((jchar >> 12) & 0x0F))));
							out->put(((char)(0x80 + ((jchar >> 6) & 0x3F))));
							out->put(((char)(0x80 + (jchar & 0x3F))));
							outRemaining -= 3;
						}
					}
				}
				pos ++ ;
			}
		}
		catch(Exception* e)
		{
			in->position(pos);
		}
	}
	in->position(pos);
	return CoderResult::__UNDERFLOW;
}

} /* namespace alinous */
