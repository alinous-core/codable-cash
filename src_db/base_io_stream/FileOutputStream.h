/*
 * FilterOutputStream.h
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_FILEOUTPUTSTREAM_H_
#define BASE_IO_STREAM_FILEOUTPUTSTREAM_H_

#include "base/RawArrayPrimitive.h"
#include "base_thread/SysMutex.h"

namespace alinous {

class File;
class UnicodeString;
class ByteBuffer;
class SysThread;


class FileOutputStream {
public:
	FileOutputStream(){};
	FileOutputStream(File *file);
	FileOutputStream(File* file, bool append);
	FileOutputStream(UnicodeString* fileName);
	FileOutputStream(UnicodeString* fileName, bool append);
	virtual ~FileOutputStream();

protected:
private:
	class FileBuffer{
	public:
		long int size;
		int num;
		ByteBuffer* buff;
		ByteBuffer* flushbuff;
		ByteBuffer* one;
		ByteBuffer* two;

		int fd;

		SysMutex mutex;
		SysThread* th;

		FileBuffer(int fd);
		~FileBuffer();
		static void* doFlush(void* param);
		void flush();
		void join();
		void write(RawArrayPrimitive<char>* buffer, int off, int len);
		void write(int b);
	};
};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_FILEOUTPUTSTREAM_H_ */
