/*
 * FilterOutputStream.h
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_FILEOUTPUTSTREAM_H_
#define BASE_IO_STREAM_FILEOUTPUTSTREAM_H_

#include "osenv/funcs.h"
#include "base_io_stream/OutputStream.h"
#include "base/RawArrayPrimitive.h"

namespace alinous {

class File;
class UnicodeString;


class FileOutputStream : public OutputStream {
public:
	FileOutputStream(const FileOutputStream& inst) = delete;

	explicit FileOutputStream(const File *file) noexcept;
	FileOutputStream(const File* file, bool append) noexcept;
	explicit FileOutputStream(const UnicodeString* fileName) noexcept;
	FileOutputStream(const UnicodeString* fileName, bool append) noexcept;
	virtual ~FileOutputStream();

	void open(bool sync);

	virtual void write(const char* buffer, int off, int len);
	virtual void write(const char* buffer, int size);
	virtual void close();
	virtual void flush();

protected:
	File* file;
	FileDescriptor fd;
	bool append;
};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_FILEOUTPUTSTREAM_H_ */
