/*
 * BlockFileHeader.cpp
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "filestore_block/BlockFileHeader.h"
#include "filestore/LongRangeList.h"
#include "base_io/ByteBuffer.h"
#include "random_access_file/RandomAccessFile.h"

#include "base/StackRelease.h"

namespace alinous {

BlockFileHeader::BlockFileHeader(RandomAccessFile* file) noexcept : file(file) {
	this->usedArea = nullptr;
}

BlockFileHeader::~BlockFileHeader() noexcept {
	clearArea();
}

void BlockFileHeader::createStore(bool del, uint64_t defaultSize) noexcept(false) {
	syncFile(defaultSize);
	clearArea();
}

void BlockFileHeader::clearArea() noexcept {
	if(this->usedArea != nullptr){
		delete this->usedArea;
		this->usedArea = nullptr;
	}
}

void BlockFileHeader::syncFile(uint64_t blockFileSize) noexcept(false) {
	this->usedArea = new LongRangeList();

	int binSize = sizeof(uint64_t) + this->usedArea->binarySize();

	ByteBuffer* buff = ByteBuffer::allocateWithEndian(binSize, true);
	StackRelease<ByteBuffer> _st_buff(buff);

	buff->putLong(blockFileSize);

	this->usedArea->toBinary(buff);
	buff->position(0);


	// sync with file
	this->file->setLength(binSize);

	const char* binary = (const char*)buff->array();
	int cnt = this->file->write(0, binary, binSize);

	assert(cnt == binSize);

	this->file->sync(true);
}

} /* namespace alinous */
