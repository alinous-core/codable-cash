/*
 * DiskCacheManager.h
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#ifndef RANDOM_ACCESS_FILE_DISKCACHEMANAGER_H_
#define RANDOM_ACCESS_FILE_DISKCACHEMANAGER_H_

#include "base/RawLinkedList.h"
#include "base_thread/SysMutex.h"

#include <stdint.h>

namespace alinous {

class MMapSegment;

class DiskCacheManager {
public:
	friend class MMapSegments;

	DiskCacheManager() noexcept;
	explicit DiskCacheManager(int maxCache) noexcept;
	virtual ~DiskCacheManager() noexcept;

	void fireCacheHit(RawLinkedList<MMapSegment>::Element* seg) noexcept;
	void fireCacheRemoved(RawLinkedList<MMapSegment>::Element* seg) noexcept;

	RawLinkedList<MMapSegment>::Element* registerCache(MMapSegment* newSeg) noexcept;

	int size() const noexcept;
protected:
	RawLinkedList<MMapSegment> cache;
	uint64_t maxCache;
	uint64_t currentSize;
	SysMutex lock;
};

} /* namespace alinous */

#endif /* RANDOM_ACCESS_FILE_DISKCACHEMANAGER_H_ */
