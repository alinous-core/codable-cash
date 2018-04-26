/*
 * RandomAccessFile.h
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#ifndef RANDOM_ACCESS_FILE_RANDOMACCESSFILE_H_
#define RANDOM_ACCESS_FILE_RANDOMACCESSFILE_H_

#include <stdint.h>

namespace alinous {

class UnicodeString;
class File;
class MMapSegments;
class DiskCacheManager;

class RandomAccessFile {
public:
	RandomAccessFile();
	virtual ~RandomAccessFile();

protected:
	File* file;
	UnicodeString* mode;
	uint64_t position;

	int fd;
	long long pageSize;
	long long fileSize;
	MMapSegments* segments;
	DiskCacheManager* diskCacheManager;

};

} /* namespace alinous */

#endif /* RANDOM_ACCESS_FILE_RANDOMACCESSFILE_H_ */
