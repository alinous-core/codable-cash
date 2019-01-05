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
#include "random_access_file/MMapSegment.h"
#include "random_access_file/DiskCacheManager.h"

#include "base/StackRelease.h"

#include "debug/debugMacros.h"

namespace alinous {

constexpr uint64_t RandomAccessFile::PAGE_NUM_CACHE;

RandomAccessFile::RandomAccessFile(const File* file, DiskCacheManager* diskCacheManager) noexcept {
	this->position = 0;
	this->fileSize = 0;
	this->diskCacheManager = diskCacheManager;

	this->file = new File(*file);
	this->segments = nullptr;
	this->pageSize = Os::getSystemPageSize();
}

RandomAccessFile::RandomAccessFile(const File* file, DiskCacheManager* diskCacheManager, uint64_t pageSize) noexcept {
	this->position = 0;
	this->fileSize = 0;
	this->diskCacheManager = diskCacheManager;

	this->file = new File(*file);
	this->segments = nullptr;
	this->pageSize = pageSize;
}

RandomAccessFile::~RandomAccessFile() noexcept {
	close();
	delete this->file;
}

void RandomAccessFile::open(bool sync) {
	ERROR_POINT(L"RandomAccessFile::open")
	this->fd = Os::openFile2ReadWrite(this->file, sync);

	if(!this->fd.isOpened()){
		throw new FileOpenException(__FILE__, __LINE__);
	}

	this->position = 0;
	this->fileSize = this->file->length();

	uint64_t segmentSize = getSegmentSize();
	this->segments = new MMapSegments(this->fileSize, segmentSize);

	if(this->fileSize == 0){
		setLength(this->pageSize * PAGE_NUM_CACHE);
	}
}

void RandomAccessFile::close() noexcept {
	if(!this->fd.isOpened()){
		return;
	}

	if(this->segments != nullptr){
		this->segments->clearElements(this->diskCacheManager, this->fd);
		delete this->segments;
		this->segments = nullptr;
	}

	Os::closeFileDescriptor(&this->fd);
}


int RandomAccessFile::read(uint64_t fpos, char* buff, int count) {
	uint64_t segSize = getSegmentSize();

	int count2Read = count;
	int currentfpos = fpos;
	while(count2Read > 0){
		MMapSegment* seg = this->segments->getSegment(currentfpos, this->diskCacheManager, this->fd);
		MMapSegmentStackRelease dec(seg);

		uint64_t offset = currentfpos % segSize;
		char* ptr = seg->getPtr(offset);
		int cnt = seg->remains(offset);
		cnt = cnt > count2Read ? count2Read : cnt;

		Mem::memcpy(buff, ptr, cnt);

		count2Read -= cnt;
		currentfpos += cnt;
		buff += cnt;
	}

	return count;
}

#ifdef __TEST_CPP_UNIT__
static int errorHook(){
	CAUSE_ERROR_BY_RETURN(L"RandomAccessFile::write", -1)
	return 0;
}

#endif


int RandomAccessFile::write(uint64_t fpos, const char* buff, int count) {
#ifdef __TEST_CPP_UNIT__
	if(errorHook() < 0){
		throw new FileIOException(__FILE__, __LINE__);
	}
#endif

	uint64_t segSize = getSegmentSize();

	int count2Write = count;
	int currentfpos = fpos;
	while(count2Write > 0){
		MMapSegment* seg = this->segments->getSegment(currentfpos, this->diskCacheManager, this->fd);
		MMapSegmentStackRelease dec(seg);

		uint64_t offset = currentfpos % segSize;
		char* ptr = seg->getPtr(offset);
		int cnt = seg->remains(offset);
		cnt = cnt > count2Write ? count2Write : cnt;

		Mem::memcpy(ptr, buff, cnt);
		seg->setDirty(true);

		count2Write -= cnt;
		currentfpos += cnt;
		buff += cnt;
	}

	return count;
}

void RandomAccessFile::sync(bool flushDisk) {
	ERROR_POINT(L"RandomAccessFile::sync")

	this->segments->sync(flushDisk, this->fd);

	if(flushDisk){
		int code = Os::syncFile(&this->fd);
		if(code < 0){
			throw new FileIOException(L"Failed in synchronizing file.", __FILE__, __LINE__);
		}
	}
}

uint64_t RandomAccessFile::getSegmentSize() const noexcept {
	return this->pageSize * PAGE_NUM_CACHE;
}

void RandomAccessFile::setLength(uint64_t newLength) noexcept(false) {
	if(!this->fd.isOpened()){
		UnicodeString* path = this->file->getAbsolutePath();
		StackRelease<UnicodeString> r_path(path);
		UnicodeString msg(path);
		msg.append(L" is not opened at setLength()");

		throw new FileIOException(msg.towString(), __FILE__, __LINE__);
	}
	if(newLength <= this->fileSize){
		return;
	}


	uint64_t newSize = newLength - this->fileSize;
	const uint64_t numBlocks = newSize / this->pageSize;
	const uint64_t modBytes = newSize % this->pageSize;

	Os::seekFile(&this->fd, 0, Os::SeekOrigin::FROM_END);

	int n;
	char *tmp = new char[this->pageSize]{};
	StackArrayRelease<char> t_tmp(tmp);

	ERROR_POINT(L"RandomAccessFile::setLength::01")

	for(int i = 0; i != numBlocks; ++i){
		n = Os::write2File(&this->fd, tmp, this->pageSize);
		if(n != this->pageSize){
			UnicodeString* path = this->file->getAbsolutePath();
			StackRelease<UnicodeString> r_path(path);
			throw new FileIOException(path->towString(), __FILE__, __LINE__);
		}
	}

	ERROR_POINT(L"RandomAccessFile::setLength::02")
	n = Os::write2File(&this->fd, tmp, modBytes);
	if(n != modBytes){
		UnicodeString* path = this->file->getAbsolutePath();
		StackRelease<UnicodeString> r_path(path);
		throw new FileIOException(path->towString(), __FILE__, __LINE__);
	}

	this->fileSize = this->file->length();
	this->segments->onResized(this->fileSize, this->fd, this->diskCacheManager);

}

MMapSegment* RandomAccessFile::getSegment(uint64_t fpos) noexcept(false) {
	return this->segments->getSegment(fpos, this->diskCacheManager, this->fd);
}

bool RandomAccessFile::exists() const noexcept {
	return this->file->exists();
}

} /* namespace alinous */
