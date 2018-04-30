/*
 * MMapSegment.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "random_access_file/MMapSegment.h"
#include "random_access_file/MMapSegments.h"
#include "base_thread/StackUnlocker.h"

#include "debug/debugMacros.h"

namespace alinous {

MMapSegment::MMapSegment(uint64_t mappedSize, uint64_t) noexcept : refCount(0), mappedSize(mappedSize)
				, position(position)
{
	this->buffer = new uint8_t[mappedSize];
}

MMapSegment::~MMapSegment() {
	delete this->buffer;
}

void MMapSegment::addRefCount() noexcept {
	StackUnlocker unlocker(&this->lock);

	this->refCount++;
}

void MMapSegment::decRefCount() noexcept {
	StackUnlocker unlocker(&this->lock);

	this->refCount--;
}

bool MMapSegment::isUsed() noexcept {
	StackUnlocker unlocker(&this->lock);
	return this->refCount != 0;
}

MMapSegmentStackRelease::MMapSegmentStackRelease(MMapSegment* ptr) noexcept : ptr(ptr){
}

MMapSegmentStackRelease::~MMapSegmentStackRelease() noexcept {
	ptr->decRefCount();
}

} /* namespace alinous */


