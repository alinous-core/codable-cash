/*
 * InputStreamReader.h
 *
 *  Created on: 2018/05/15
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_INPUTSTREAMREADER_H_
#define BASE_IO_STREAM_INPUTSTREAMREADER_H_

#include "base_io_stream/Reader.h"

namespace alinous {

class InputStream;
class UnicodeString;
class ByteBuffer;
class CharBuffer;

class InputStreamReader : public Reader {
public:
	InputStreamReader(InputStream* in, UnicodeString* charsetName);
	explicit InputStreamReader(InputStream* in);
	virtual ~InputStreamReader();

	virtual void close();
	virtual int read(wchar_t* b, int off, int len);
	virtual int read(wchar_t* b, int size);

private:
	void init() noexcept;
	void initBuffer(int estimatedLength) noexcept;
	int __read(wchar_t* b, int off, int len);
	void setupRemainCharBuffer(int diff) noexcept;

	InputStream* stream;
	UnicodeString* charsetName;

	char* buffer;
	int bufferLength;

	ByteBuffer* bytes;
	ByteBuffer* remainBytes;
	CharBuffer* chars;
	CharBuffer* charsRemain;
};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_INPUTSTREAMREADER_H_ */
