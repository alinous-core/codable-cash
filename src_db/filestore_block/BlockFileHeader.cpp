/*
 * BlockFileHeader.cpp
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "filestore_block/BlockFileHeader.h"
#include "filestore_block/exceptions.h"

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

void BlockFileHeader::createStore(bool del, uint64_t defaultSize, uint64_t blockSize) noexcept(false) {
	sync2File(blockSize);
	sync();

	clearArea();
}

void BlockFileHeader::clearArea() noexcept {
	if(this->usedArea != nullptr){
		delete this->usedArea;
		this->usedArea = nullptr;
	}
}

void BlockFileHeader::sync2File() noexcept(false) {
	sync2File(this->bodySize);
}

void BlockFileHeader::sync2File(uint64_t blockFileSize) noexcept(false) {
	this->usedArea = new LongRangeList();
	this->bodySize = blockFileSize;

	uint32_t headSize = sizeof(uint64_t)*2;
	int binSize = headSize + this->usedArea->binarySize();

	ByteBuffer* buff = ByteBuffer::allocateWithEndian(binSize, true);
	StackRelease<ByteBuffer> _st_buff(buff);

	buff->putLong(blockFileSize);

	this->usedArea->toBinary(buff);
	buff->position(0);


	// sync with file
	this->file->setLength(binSize + headSize);

	// file size
	ByteBuffer* buffSizeHeader = ByteBuffer::allocateWithEndian(headSize, true);
	StackRelease<ByteBuffer> _st_buffSizeHeader(buffSizeHeader);
	buffSizeHeader->putLong(binSize);
	buffSizeHeader->putLong(blockFileSize);
	buffSizeHeader->position(0);

	uint64_t fpos = 0;
	const char* binary = (const char*)buffSizeHeader->array();
	fpos += this->file->write(fpos, binary, sizeof(int64_t));

	// content
	binary = (const char*)buff->array();
	int cnt = this->file->write(fpos, binary, binSize);
	assert(cnt == binSize);
}

void BlockFileHeader::sync() noexcept(false) {
	this->file->sync(true);
}

void BlockFileHeader::loadFromFile() {
	uint64_t fpos = 0;
	uint32_t headSize = sizeof(uint64_t)*2;
	char sizeHeaderBinary[headSize]{};
	fpos += this->file->read(fpos, sizeHeaderBinary, headSize);

	ByteBuffer* buffSizeHeader = ByteBuffer::allocateWithEndian(headSize, true);
	StackRelease<ByteBuffer> _st_buffSizeHeader(buffSizeHeader);

	buffSizeHeader->put((const uint8_t*)sizeHeaderBinary, headSize);

	buffSizeHeader->position(0);
	int64_t loadSize = buffSizeHeader->getLong();
	this->bodySize = buffSizeHeader->getLong();

	int areaSize = loadSize - headSize;
	if(areaSize < 4){
		throw new BlockFileStorageException(L"File header format is broken", __FILE__, __LINE__);
	}

	char* usedAreaBinary = new char[areaSize]{};
	StackArrayRelease<char> st_usedAreaBinary(usedAreaBinary);
	fpos += this->file->read(fpos, sizeHeaderBinary, areaSize);

	ByteBuffer* rangeBinary = ByteBuffer::allocateWithEndian(areaSize, true);
	StackRelease<ByteBuffer> _st_rangeBinary(rangeBinary);

	rangeBinary->put((unsigned char*)usedAreaBinary, areaSize);
	rangeBinary->position(0);
	this->usedArea = LongRangeList::fromBinary(rangeBinary);
}

uint64_t BlockFileHeader::alloc() {
	uint64_t pos = this->usedArea->firstEmpty();

	this->usedArea->addRange(pos);

	return pos;
}



} /* namespace alinous */


