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
class DiskCacheManager;

class RandomAccessFile {
public:
	RandomAccessFile(const File* file, DiskCacheManager* diskCacheManager) noexcept;
	virtual ~RandomAccessFile() noexcept;

	void open();
	void setLength(uint64_t newLength);
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
