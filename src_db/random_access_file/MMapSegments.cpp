/*
 * MMapSegments.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "random_access_file/MMapSegments.h"

namespace alinous {

MMapSegments::MMapSegments(uint64_t fileSize, uint64_t segmentSize) noexcept
		: fileSize(fileSize), segmentSize(segmentSize) {
	int numSegments = (fileSize % segmentSize) == 0 ? fileSize / segmentSize : (fileSize / segmentSize) + 1;
	this->numSegments = numSegments;
}

MMapSegments::~MMapSegments() noexcept {

}

void alinous::MMapSegments::onResized(uint64_t fileSize) {

}


} /* namespace alinous */

