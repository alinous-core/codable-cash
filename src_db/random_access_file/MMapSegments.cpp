/*
 * MMapSegments.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "random_access_file/MMapSegments.h"
#include "random_access_file/MMapSegment.h"

#include "base_thread/StackUnlocker.h"

#include "debug/debugMacros.h"

namespace alinous {

MMapSegments::MMapSegments(uint64_t fileSize, uint64_t segmentSize) noexcept
		: fileSize(fileSize), segmentSize(segmentSize) {
	int numSegments = getNumSegments(fileSize, segmentSize);
	this->numSegments = numSegments;

	StackUnlocker stackLock(&this->lock);

	this->segIndex = new ArrayList<MMapSegment>(numSegments);
	for(int i = 0; i != numSegments; ++i){
		this->segIndex->addElement(nullptr);
	}
}

MMapSegments::~MMapSegments() noexcept {
	int maxLoop = this->segIndex->size();
	for(int i = 0; i != maxLoop; ++i){
		MMapSegment* seg = this->segIndex->get(i);
		if(seg != nullptr){
			delete seg;
		}
	}

	delete this->segIndex;
}

uint64_t MMapSegments::getNumSegments(uint64_t fileSize, uint64_t segmentSize) const noexcept {
	return (fileSize % segmentSize) == 0 ? fileSize / segmentSize : (fileSize / segmentSize) + 1;
}

void MMapSegments::onResized(uint64_t fileSize) {
	StackUnlocker stackLock(&this->lock);

	if(fileSize <=  this->fileSize){
		return;
	}

	int lastTopSegment = this->segIndex->size() - 1;

	int newNumSegments = getNumSegments(fileSize, segmentSize);

	uint64_t diffSize = newNumSegments - this->numSegments;
	for(uint64_t i = 0; i != diffSize; ++i){
		this->segIndex->addElement(nullptr);
	}

	this->numSegments = newNumSegments;
	this->fileSize = fileSize;

	// TODO: hadle last seg
	if(lastTopSegment < 0 || this->segIndex->get(lastTopSegment) == nullptr){
		return;
	}
}


} /* namespace alinous */

