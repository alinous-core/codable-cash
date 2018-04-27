/*
 * MMapSegment.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "random_access_file/MMapSegment.h"
#include "random_access_file/MMapSegments.h"

#include "debug/debugMacros.h"

namespace alinous {

MMapSegment::MMapSegment(uint64_t mappedSize, uint64_t) noexcept : refCount(0), mappedSize(mappedSize)
				, position(position)
{
	this->buffer = new uint8_t[mappedSize];
}

MMapSegment::~MMapSegment() {
	delete this->buffer;
}

} /* namespace alinous */

