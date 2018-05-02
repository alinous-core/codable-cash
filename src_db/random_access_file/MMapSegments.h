/*
 * MMapSegments.h
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#ifndef RANDOM_ACCESS_FILE_MMAPSEGMENTS_H_
#define RANDOM_ACCESS_FILE_MMAPSEGMENTS_H_

#include <stdint.h>

#include "base/RawArrayPrimitive.h"
#include "base/ArrayList.h"
#include "base/RawLinkedList.h"
#include "base_thread/SysMutex.h"
#include "osenv/funcs.h"

namespace alinous {

class MMapSegment;
class DiskCacheManager;

class MMapSegments {
public:
	MMapSegments(uint64_t fileSize, uint64_t segmentSize) noexcept;
	virtual ~MMapSegments() noexcept;

	void clearElements(DiskCacheManager *diskManager) noexcept;

	void onResized(uint64_t fileSize) noexcept;
	MMapSegment* getSegment(uint64_t fpos, DiskCacheManager *cache, FileDescriptor& fd);
	MMapSegment* newSegment(uint64_t fpos, FileDescriptor& fd);
	void requestCacheOut(MMapSegment* seg) noexcept;
	void cacheOutSegmentIndex() noexcept;

	void sync(bool flushDisk, FileDescriptor& fd);

protected:
	uint64_t getNumSegments(uint64_t fileSize, uint64_t segmentSize) const noexcept;


protected:
	ArrayList<RawLinkedList<MMapSegment>::Element>* segIndex;
	uint64_t numSegments;
	uint64_t segmentSize;
	uint64_t fileSize;


	RawArrayPrimitive<int> removeList;
	SysMutex lock;
};

} /* namespace alinous */

#endif /* RANDOM_ACCESS_FILE_MMAPSEGMENTS_H_ */
