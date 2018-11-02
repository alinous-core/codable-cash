/*
 * BlockFileHeader.cpp
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#include "filestore_block/BlockFileHeader.h"
#include "filestore/LongRangeList.h"

namespace alinous {

BlockFileHeader::BlockFileHeader(RandomAccessFile* file) noexcept : file(file) {
	this->usedArea = nullptr;
}

BlockFileHeader::~BlockFileHeader() noexcept {
	if(this->usedArea != nullptr){
		delete this->usedArea;
	}
}

void BlockFileHeader::createStore(bool del, uint64_t defaultSize) noexcept(false) {
	this->usedArea = new LongRangeList();

	delete this->usedArea;
}

} /* namespace alinous */
