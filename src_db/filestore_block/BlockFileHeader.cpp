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
	clearArea();
}

void BlockFileHeader::createStore(bool del) noexcept(false) {
	this->usedArea = new LongRangeList();

	clearArea();
}

void BlockFileHeader::clearArea() noexcept {
	if(this->usedArea != nullptr){
		delete this->usedArea;
		this->usedArea = nullptr;
	}
}

} /* namespace alinous */
