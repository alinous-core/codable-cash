/*
 * RandomAccessFile.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "random_access_file/RandomAccessFile.h"


#include "base/UnicodeString.h"
#include "base_io/File.h"
#include "base_io_stream/exceptions.h"

#include "random_access_file/MMapSegments.h"
#include "random_access_file/DiskCacheManager.h"

#include "base/StackRelease.h"

namespace alinous {

constexpr uint64_t RandomAccessFile::PAGE_NUM_CACHE;

RandomAccessFile::RandomAccessFile(const File* file, DiskCacheManager* diskCacheManager) noexcept
				: position(0), fd(), fileSize(0), diskCacheManager(diskCacheManager){
	this->file = new File(*file);
	this->segments = nullptr;
	this->pageSize = Os::getSystemPageSize();
}

RandomAccessFile::~RandomAccessFile() noexcept {
	delete this->file;
	delete this->segments;
}

void RandomAccessFile::open() {
	this->fd = Os::openFile2ReadWrite(this->file, true);

	if(!this->fd.isOpened()){
		throw new FileOpenException(__FILE__, __LINE__);
	}

	this->position = 0;
	this->fileSize = this->file->length();

	if(this->fileSize == 0){
		setLength(this->pageSize * PAGE_NUM_CACHE);
	}

	uint64_t segmentSize = this->pageSize * PAGE_NUM_CACHE;
	this->segments = new MMapSegments(this->fileSize, segmentSize);
}

void RandomAccessFile::setLength(uint64_t newLength) {
	if(!this->fd.isOpened()){
		UnicodeString* path = this->file->getAbsolutePath();
		StackRelease<UnicodeString> r_path(path);
		UnicodeString msg(path);
		msg.append(L" is not opened at setLength()");

		throw new FileIOException(&msg, __FILE__, __LINE__);
	}

	uint64_t newSize = newLength - this->fileSize;
	const uint64_t numBlocks = newSize / this->pageSize;
	const uint64_t modBytes = newSize % this->pageSize;

	Os::seekFile(&this->fd, 0, Os::SeekOrigin::FROM_END);

	int n;
	char *tmp = new char[this->pageSize]{};
	StackArrayRelease<char> t_tmp(tmp);

	for(int i = 0; i != numBlocks; ++i){
		n = Os::write2File(&this->fd, tmp, this->pageSize);
		if(n != this->pageSize){
			UnicodeString* path = this->file->getAbsolutePath();
			StackRelease<UnicodeString> r_path(path);
			throw new FileIOException(path, __FILE__, __LINE__);
		}
	}

	n = Os::write2File(&this->fd, tmp, modBytes);
	if(n != modBytes){
		UnicodeString* path = this->file->getAbsolutePath();
		StackRelease<UnicodeString> r_path(path);
		throw new FileIOException(path, __FILE__, __LINE__);
	}

	this->fileSize = this->file->length();
	this->segments->onResized(this->fileSize);

}

} /* namespace alinous */
