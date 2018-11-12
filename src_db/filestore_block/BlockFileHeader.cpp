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
	this->bodySize = 0;
}

BlockFileHeader::~BlockFileHeader() noexcept {
	clearArea();
}

void BlockFileHeader::createStore(bool del, uint64_t defaultSize) noexcept(false) {
	sync2File(defaultSize);
	clearArea();
}

void BlockFileHeader::clearArea() noexcept {
	if(this->usedArea != nullptr){
		delete this->usedArea;
		this->usedArea = nullptr;
	}
}

void BlockFileHeader::sync2File(uint64_t blockFileSize) noexcept(false) {
	this->usedArea = new LongRangeList();
	this->bodySize = blockFileSize;

	int binSize = sizeof(uint64_t) + this->usedArea->binarySize();

	ByteBuffer* buff = ByteBuffer::allocateWithEndian(binSize, true);
	StackRelease<ByteBuffer> _st_buff(buff);

	buff->putLong(blockFileSize);

	this->usedArea->toBinary(buff);
	buff->position(0);


	// sync with file
	this->file->setLength(binSize + sizeof(uint64_t));

	// file size
	ByteBuffer* buffSizeHeader = ByteBuffer::allocateWithEndian(sizeof(int64_t), true);
	StackRelease<ByteBuffer> _st_buffSizeHeader(buffSizeHeader);
	buffSizeHeader->putLong(binSize);
	buffSizeHeader->position(0);

	uint64_t fpos = 0;
	const char* binary = (const char*)buffSizeHeader->array();
	fpos += this->file->write(fpos, binary, sizeof(int64_t));

	// content
	binary = (const char*)buff->array();
//	int cnt = this->file->write(fpos, binary, binSize);
//	assert(cnt == binSize);

	this->file->sync(true);
}

void BlockFileHeader::loadFromFile() {
	uint64_t fpos = 0;
	char sizeHeaderBinary[sizeof(uint64_t)]{'A'};
	this->file->read(fpos, sizeHeaderBinary, sizeof(uint64_t));

	ByteBuffer* buffSizeHeader = ByteBuffer::allocateWithEndian(sizeof(uint64_t), true);
	StackRelease<ByteBuffer> _st_buffSizeHeader(buffSizeHeader);

	buffSizeHeader->put((const uint8_t*)sizeHeaderBinary, sizeof(uint64_t));
	int64_t loadSize = buffSizeHeader->getLong(0);

	loadSize++;

}

} /* namespace alinous */
