/*
 * DiskCacheManager.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "random_access_file/DiskCacheManager.h"
#include "random_access_file/MMapSegment.h"

#include "base_thread/StackUnlocker.h"

#include "debug/debugMacros.h"

namespace alinous {

DiskCacheManager::DiskCacheManager() noexcept {
	this->maxCache = Os::getSystemPageSize() * 4 * 4;
	this->currentSize = 0;
}


DiskCacheManager::DiskCacheManager(int maxCache) noexcept {
	this->maxCache = maxCache;
	this->currentSize = 0;
}

DiskCacheManager::~DiskCacheManager() noexcept{

}

void DiskCacheManager::fireCacheHit(RawLinkedList<MMapSegment>::Element* seg) noexcept {
	StackUnlocker locker(&this->lock);
	this->cache.moveElementToTop(seg);
}

void DiskCacheManager::fireCacheRemoved(RawLinkedList<MMapSegment>::Element* seg) noexcept {
	StackUnlocker locker(&this->lock);

	MMapSegment* data = seg->data;
	this->currentSize -= data->segmentSize();
	this->cache.remove(seg);
}

RawLinkedList<MMapSegment>::Element* DiskCacheManager::registerCache(MMapSegment* newSeg) noexcept
{
	StackUnlocker locker(&this->lock);

	if(this->maxCache <= this->currentSize){
		RawLinkedList<MMapSegment>::Element* outSeg = this->cache.getLastElement();
		MMapSegment* segdata = outSeg->data;

		segdata->waitForUnused();

		// request delete from segment index
		segdata->requestCacheOut();
		this->currentSize -= segdata->segmentSize();

		this->cache.remove(this->cache.size() - 1);
	}

	RawLinkedList<MMapSegment>::Element* newElement = this->cache.add(0, newSeg);
	this->currentSize += newSeg->segmentSize();

	return newElement;
}

int DiskCacheManager::size() const noexcept {
	return this->currentSize;
}

} /* namespace alinous */

