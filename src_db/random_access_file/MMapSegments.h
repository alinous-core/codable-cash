/*
 * MMapSegments.h
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#ifndef RANDOM_ACCESS_FILE_MMAPSEGMENTS_H_
#define RANDOM_ACCESS_FILE_MMAPSEGMENTS_H_

#include <stdint.h>

#include "base/ArrayList.h"
#include "base_thread/SysMutex.h"

namespace alinous {

class MMapSegment;

class MMapSegments {
public:
	MMapSegments(uint64_t fileSize, uint64_t segmentSize) noexcept;
	virtual ~MMapSegments() noexcept;

	void onResized(uint64_t fileSize);

protected:
	ArrayList<MMapSegment>* segIndex;
	uint64_t numSegments;
	uint64_t segmentSize;
	uint64_t fileSize;

	SysMutex lock;
};

} /* namespace alinous */

#endif /* RANDOM_ACCESS_FILE_MMAPSEGMENTS_H_ */
