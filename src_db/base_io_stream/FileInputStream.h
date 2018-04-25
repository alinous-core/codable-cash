/*
 * FileInputStream.h
 *
 *  Created on: 2018/04/25
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_FILEINPUTSTREAM_H_
#define BASE_IO_STREAM_FILEINPUTSTREAM_H_

#include "base_io_stream/InputStream.h"
#include "osenv/funcs.h"

namespace alinous {

class File;
class UnicodeString;

class FileInputStream : public InputStream {
public:
	FileInputStream(const File *file) noexcept;
	FileInputStream(const UnicodeString* fileName) noexcept;
	virtual ~FileInputStream();

	void open();
	virtual void close();
	virtual int read(char* b, int off, int len);
	virtual int read();
	virtual int available();

protected:
	File* file;
	FileDescriptor fd;
};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_FILEINPUTSTREAM_H_ */
