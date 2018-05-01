/*
 * DiskCacheManager.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "random_access_file/DiskCacheManager.h"
#include "base_thread/StackUnlocker.h"

#include "debug/debugMacros.h"

namespace alinous {

DiskCacheManager::DiskCacheManager() noexcept{
	// TODO Auto-generated constructor stub

}

DiskCacheManager::~DiskCacheManager() noexcept{
	// TODO Auto-generated destructor stub
}

void DiskCacheManager::fireCacheHit(RawLinkedList<MMapSegment>::Element* seg) noexcept {
	StackUnlocker locker(&this->lock);
	this->cache.moveElementToTop(seg);
}

RawLinkedList<MMapSegment>::Element* DiskCacheManager::registerCache(
		MMapSegment* newSeg) noexcept
{
	StackUnlocker locker(&this->lock);
	RawLinkedList<MMapSegment>::Element* newElement = this->cache.add(0, newSeg);

	return newElement;
}


} /* namespace alinous */

