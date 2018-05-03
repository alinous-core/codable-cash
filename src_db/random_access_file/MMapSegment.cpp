/*
 * MMapSegment.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "random_access_file/MMapSegment.h"
#include "random_access_file/MMapSegments.h"
#include "base_thread/StackUnlocker.h"

#include "base_io_stream/exceptions.h"

#include "debug/debugMacros.h"

namespace alinous {

MMapSegment::MMapSegment(uint64_t mappedSize, uint64_t position, MMapSegments* parent) noexcept
{
	this->refCount = 0;
	this->mappedSize = mappedSize;
	this->position = position;
	this->parent = parent;
	this->dirty = false;
	this->buffer = new uint8_t[this->mappedSize];
}

MMapSegment::~MMapSegment() {
	delete [] this->buffer;
}

void MMapSegment::addRefCount() noexcept {
	StackUnlocker unlocker(&this->lock);

	this->refCount++;
}

void MMapSegment::decRefCount() noexcept {
	StackUnlocker unlocker(&this->lock);

	this->refCount--;
	this->lock.notifyAll();
}

/*
bool MMapSegment::isUsed() noexcept {
	StackUnlocker unlocker(&this->lock);
	return this->refCount != 0;
}
*/
void MMapSegment::waitForUnused() noexcept {
	StackUnlocker unlocker(&this->lock);

	if(this->refCount != 0){
		this->lock.wait();
	}
}

void MMapSegment::requestCacheOut() noexcept {
	this->parent->requestCacheOut(this);
}

void MMapSegment::loadData(FileDescriptor& fd) {
	ERROR_POINT(L"MMapSegment::loadData::01")

	int ret = Os::seekFile(&fd, this->position, Os::SeekOrigin::FROM_BEGINING);
	if(ret < 0){
		throw new FileIOException(__FILE__, __LINE__);
	}

	ERROR_POINT(L"MMapSegment::loadData::02")

	ret = Os::readFile(&fd, (char*)this->buffer, this->mappedSize);
	if(ret != this->mappedSize){
		throw new FileIOException(__FILE__, __LINE__);
	}
}

uint8_t* MMapSegment::getPtr(uint64_t offset) const noexcept {
	assert(offset < this->mappedSize);
	return this->buffer + offset;
}

void MMapSegment::setDirty(bool dirty) noexcept {
	this->dirty = dirty;
}
bool MMapSegment::isDirty() const noexcept {
	return this->dirty;
}

uint64_t MMapSegment::remains(uint64_t offset) const noexcept {
	return this->mappedSize - offset;
}


MMapSegmentStackRelease::MMapSegmentStackRelease(MMapSegment* ptr) noexcept {
	this->ptr = ptr;
}

MMapSegmentStackRelease::~MMapSegmentStackRelease() noexcept {
	ptr->decRefCount();
}

int MMapSegment::writeBack(FileDescriptor& fd) {
	ERROR_POINT(L"MMapSegment::writeBack")

	int ret = Os::write2File(&fd, (char*)this->buffer, this->mappedSize);

	if(ret != this->mappedSize){
		throw new FileIOException(__FILE__, __LINE__);
	}

	this->dirty = false;

	return ret;
}

} /* namespace alinous */


