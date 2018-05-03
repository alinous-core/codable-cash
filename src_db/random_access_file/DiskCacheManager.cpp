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

DiskCacheManager::DiskCacheManager(int maxCache) noexcept {
	this->maxCache = maxCache;
}

DiskCacheManager::~DiskCacheManager() noexcept{

}

void DiskCacheManager::fireCacheHit(RawLinkedList<MMapSegment>::Element* seg) noexcept {
	StackUnlocker locker(&this->lock);
	this->cache.moveElementToTop(seg);
}

void DiskCacheManager::fireCacheRemoved(RawLinkedList<MMapSegment>::Element* seg) noexcept {
	StackUnlocker locker(&this->lock);

	this->cache.remove(seg);
}

RawLinkedList<MMapSegment>::Element* DiskCacheManager::registerCache(
		MMapSegment* newSeg) noexcept
{
	StackUnlocker locker(&this->lock);

	if(this->maxCache <= this->cache.size()){
		RawLinkedList<MMapSegment>::Element* outSeg = this->cache.getLastElement();

		outSeg->data->waitForUnused();

		// request delete from segment index
		outSeg->data->requestCacheOut();

		MMapSegment* seg = this->cache.remove(this->cache.size() - 1);
		delete seg;
	}

	RawLinkedList<MMapSegment>::Element* newElement = this->cache.add(0, newSeg);
	return newElement;
}

int DiskCacheManager::size() const noexcept {
	return this->cache.size();
}

} /* namespace alinous */

