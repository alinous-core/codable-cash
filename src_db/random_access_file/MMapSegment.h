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
#include "osenv/funcs.h"

namespace alinous {

class MMapSegments;

class MMapSegment {
public:
	friend class MMapSegments;

	MMapSegment(uint64_t mappedSize, uint64_t position, MMapSegments* parent) noexcept;
	virtual ~MMapSegment();


	void addRefCount() noexcept;
	void decRefCount() noexcept;
	//bool isUsed() noexcept;
	void waitForUnused() noexcept;
	void requestCacheOut() noexcept;

	void loadData(FileDescriptor& fd);

	uint8_t* getPtr(uint64_t offset) const noexcept;
	uint64_t remains(uint64_t offset) const noexcept;

	void setDirty(bool dirty) noexcept;
	bool isDirty() const noexcept;

	int writeBack(FileDescriptor& fd);
protected:
	uint64_t mappedSize;
	uint64_t position;
	uint8_t* buffer;

	SynchronizedLock lock;
	int refCount;
	MMapSegments* parent;

	bool dirty;
};

class MMapSegmentStackRelease {
public:
	explicit MMapSegmentStackRelease(MMapSegment* ptr) noexcept;
	~MMapSegmentStackRelease() noexcept;
private:
	MMapSegment* ptr;
};


} /* namespace alinous */

#endif /* RANDOM_ACCESS_FILE_MMAPSEGMENT_H_ */
