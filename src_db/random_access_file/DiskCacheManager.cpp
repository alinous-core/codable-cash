/*
 * DiskCacheManager.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "random_access_file/DiskCacheManager.h"

#include "debug/debugMacros.h"

namespace alinous {

DiskCacheManager::DiskCacheManager() noexcept{
	// TODO Auto-generated constructor stub

}

DiskCacheManager::~DiskCacheManager() noexcept{
	// TODO Auto-generated destructor stub
}

void DiskCacheManager::fireCacheHit(RawLinkedList<MMapSegment>::Element* seg) noexcept {

}

} /* namespace alinous */
