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

namespace alinous {

class MMapSegment {
public:
	MMapSegment();
	virtual ~MMapSegment();

protected:
	int refCount;
	uint64_t mappedSize;
};

} /* namespace alinous */

#endif /* RANDOM_ACCESS_FILE_MMAPSEGMENT_H_ */
