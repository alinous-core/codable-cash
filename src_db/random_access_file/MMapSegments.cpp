/*
 * MMapSegments.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "random_access_file/MMapSegments.h"
#include "random_access_file/MMapSegment.h"
#include "random_access_file/DiskCacheManager.h"

#include "base/UnicodeString.h"
#include "base_thread/StackUnlocker.h"
#include "base_io_stream/exceptions.h"

#include "debug/debugMacros.h"

namespace alinous {

MMapSegments::MMapSegments(uint64_t fileSize, uint64_t segmentSize) noexcept
		: fileSize(fileSize), segmentSize(segmentSize), removeList(64) {
	int numSegments = getNumSegments(fileSize, segmentSize);
	this->numSegments = numSegments;

	StackUnlocker stackLock(&this->lock);

	this->segIndex = new ArrayList<RawLinkedList<MMapSegment>::Element>(numSegments);
	for(int i = 0; i != numSegments; ++i){
		this->segIndex->addElement(nullptr);
	}
}

MMapSegments::~MMapSegments() noexcept {
	delete this->segIndex;
}

void MMapSegments::clearElements(DiskCacheManager* diskManager) noexcept {
	int maxLoop = this->segIndex->size();
	for(int i = 0; i != maxLoop; ++i){
		RawLinkedList<MMapSegment>::Element* seg = this->segIndex->get(i);
		if(seg != nullptr){
			MMapSegment* data = seg->data;
			diskManager->fireCacheRemoved(seg);
			delete data;
		}
	}
}

uint64_t MMapSegments::getNumSegments(uint64_t fileSize, uint64_t segmentSize) const noexcept {
	return (fileSize % segmentSize) == 0 ? fileSize / segmentSize : (fileSize / segmentSize) + 1;
}

void MMapSegments::onResized(uint64_t fileSize) noexcept {
	StackUnlocker stackLock(&this->lock);

	assert(fileSize >  this->fileSize);

	int lastTopSegment = this->segIndex->size() - 1;

	int newNumSegments = getNumSegments(fileSize, segmentSize);

	uint64_t diffSize = newNumSegments - this->numSegments;
	for(uint64_t i = 0; i != diffSize; ++i){
		this->segIndex->addElement(nullptr);
	}

	this->numSegments = newNumSegments;
	this->fileSize = fileSize;

	// TODO: hadle last seg
	if(lastTopSegment < 0 || this->segIndex->get(lastTopSegment) == nullptr){
		return;
	}
}

MMapSegment* MMapSegments::getSegment(uint64_t fpos, DiskCacheManager* cache, FileDescriptor fd) {
	StackUnlocker stackLock(&this->lock);

	cacheOutSegmentIndex();

	int index = (int)(fpos / this->segmentSize);

	RawLinkedList<MMapSegment>::Element* seg = this->segIndex->get(index);
	if(seg != nullptr){
		cache->fireCacheHit(seg);
		seg->data->addRefCount();
		return seg->data;
	}

	MMapSegment* newSeg = newSegment(fpos, fd);
	RawLinkedList<MMapSegment>::Element* segElement = cache->registerCache(newSeg);
	this->segIndex->setElement(segElement, index);

	return newSeg;
}

MMapSegment* MMapSegments::newSegment(uint64_t fpos, FileDescriptor fd) {
	uint64_t offset = fpos % this->segmentSize;
	uint64_t segPos = fpos - offset;

	uint64_t segSize = this->fileSize - segPos;
	if(segSize > this->segmentSize){
		segSize = this->segmentSize;
	}

	MMapSegment* seg = new MMapSegment(segSize, segPos, this);
	try{
		seg->loadData(fd);
	}catch(Exception* e){
		delete seg;

		UnicodeString msg(L"Failed in making new cache segment");
		throw new FileIOException(&msg, e, __FILE__, __LINE__);
	}

	return seg;
}

void MMapSegments::requestCacheOut(MMapSegment* seg) noexcept {
	int index = seg->position / this->segmentSize;
	this->removeList.addElement(index);
}

void MMapSegments::cacheOutSegmentIndex() noexcept {
	int maxLoop = this->removeList.size();
	for(int i = 0; i != maxLoop; ++i){
		int index = this->removeList.get(i);
		this->segIndex->setElement(nullptr, index);
	}

	this->removeList.reset();
}


} /* namespace alinous */

