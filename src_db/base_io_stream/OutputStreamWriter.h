/*
 * OutputStreamWriter.h
 *
 *  Created on: 2018/05/10
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_OUTPUTSTREAMWRITER_H_
#define BASE_IO_STREAM_OUTPUTSTREAMWRITER_H_

#include "base_io_stream/Writer.h"

namespace alinous {

class OutputStream;
class UnicodeString;

class OutputStreamWriter: public Writer {
public:
	OutputStreamWriter(const OutputStreamWriter& base) = delete;
	OutputStreamWriter(OutputStream* out, UnicodeString* charsetName);
	explicit OutputStreamWriter(OutputStream* out);
	virtual ~OutputStreamWriter();

	virtual void close();
	virtual void flush();
	virtual void write(const wchar_t* cbuf);
	virtual void write(const wchar_t* cbuf, int size);
	virtual void write(const wchar_t* cbuf, int off, int len);
	virtual void write(const UnicodeString* str, int off, int len);
	virtual void write(const UnicodeString* str);

private:
	OutputStream* out;
	UnicodeString* charsetName;
};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_OUTPUTSTREAMWRITER_H_ */
