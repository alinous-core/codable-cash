/*
 * MMapSegment.h
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#ifndef RANDOM_ACCESS_FILE_MMAPSEGMENT_H_
#define RANDOM_ACCESS_FILE_MMAPSEGMENT_H_

#include <stdint.h>
#include "base/ArrayList.h"
#include "base_thread/SynchronizedLock.h"

namespace alinous {

class MMapSegments;

class MMapSegment {
public:
	friend class MMapSegments;

	MMapSegment(uint64_t mappedSize, uint64_t position) noexcept;
	virtual ~MMapSegment();

	void addRefCount() noexcept;
	void decRefCount() noexcept;
	bool isUsed() noexcept;

protected:
	uint64_t mappedSize;
	uint64_t position;
	uint8_t* buffer;

	SynchronizedLock lock;
	int refCount;
};

class MMapSegmentStackRelease {
public:
	MMapSegmentStackRelease(MMapSegment* ptr) noexcept;
	~MMapSegmentStackRelease() noexcept;
private:
	MMapSegment* ptr;
};


} /* namespace alinous */

#endif /* RANDOM_ACCESS_FILE_MMAPSEGMENT_H_ */
