/*
 * RandomAccessFile.h
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#ifndef RANDOM_ACCESS_FILE_RANDOMACCESSFILE_H_
#define RANDOM_ACCESS_FILE_RANDOMACCESSFILE_H_

#include <stdint.h>

#include "osenv/funcs.h"

namespace alinous {

class UnicodeString;
class File;
class MMapSegments;
class MMapSegment;
class DiskCacheManager;

class RandomAccessFile {
public:
	RandomAccessFile(const RandomAccessFile& base) = delete;
	RandomAccessFile(const File* file, DiskCacheManager* diskCacheManager) noexcept;
	RandomAccessFile(const File* file, DiskCacheManager* diskCacheManager, uint64_t pageSize) noexcept;
	virtual ~RandomAccessFile() noexcept;

	void open(bool sync=false);
	void close() noexcept;
	void setLength(uint64_t newLength);

	int read(uint64_t fpos, char* buff, int count);
	int write(uint64_t fpos, const char* buff, int count);
	void sync(bool flushDisk);

	MMapSegment* getSegment(uint64_t fpos);
protected:
	constexpr static uint64_t PAGE_NUM_CACHE{4};

	uint64_t getSegmentSize() const noexcept;

protected:
	File* file;
	uint64_t position;

	FileDescriptor fd;
	uint64_t pageSize;
	uint64_t fileSize;
	MMapSegments* segments;
	DiskCacheManager* diskCacheManager;

};

} /* namespace alinous */

#endif /* RANDOM_ACCESS_FILE_RANDOMACCESSFILE_H_ */
