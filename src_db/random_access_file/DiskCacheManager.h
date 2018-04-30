/*
 * DiskCacheManager.h
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#ifndef RANDOM_ACCESS_FILE_DISKCACHEMANAGER_H_
#define RANDOM_ACCESS_FILE_DISKCACHEMANAGER_H_

#include "base/RawLinkedList.h"

namespace alinous {

class MMapSegment;

class DiskCacheManager {
public:
	friend class MMapSegments;

	DiskCacheManager() noexcept;
	virtual ~DiskCacheManager() noexcept;

protected:
	void fireCacheHit(RawLinkedList<MMapSegment>::Element* seg) noexcept;
protected:
	RawLinkedList<MMapSegment> cache;
};

} /* namespace alinous */

#endif /* RANDOM_ACCESS_FILE_DISKCACHEMANAGER_H_ */
