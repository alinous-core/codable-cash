/*
 * BlockData.cpp
 *
 *  Created on: 2018/11/20
 *      Author: iizuka
 */

#include "filestore_block/BlockData.h"

#include "base_io/ReverseByteBuffer.h"
#include "base/StackRelease.h"

#include "osenv/memory.h"

namespace alinous {

BlockData::BlockData(uint16_t blockSize, uint64_t fpos, uint16_t used, uint64_t nextfpos, const char* data) noexcept {
	this->blockSize = blockSize;
	this->currentfPos = fpos;

	this->used = used;
	this->nextfpos = nextfpos;

	this->data = new char[dataSize()]{};
	Mem::memcpy(this->data, data, used);
}

BlockData::~BlockData() {
	delete [] this->data;
}

BlockData* BlockData::createNewBlock(uint64_t blockSize, uint64_t fpos, uint16_t used, uint64_t nextfpos) {
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(blockSize, true);
	StackRelease<ByteBuffer> _st_buff(buff);

	buff->putLong(fpos);
	buff->putLong(nextfpos);
	buff->putShort(used);

	buff->position(0);
	const char* data = ((const char*)buff->array()) + HEADER_SIZE;

	return new BlockData(blockSize, fpos, used, nextfpos, data);
}

BlockData* BlockData::fromBinary(uint64_t blockSize, const char* bin, int length) {
	ByteBuffer* buff = ByteBuffer::wrapWithEndian((const uint8_t*)bin, length, true);
	StackRelease<ByteBuffer> _st_buff(buff);

	uint64_t fpos = buff->getLong();
	uint64_t nextfpos = buff->getLong();
	uint16_t used = buff->getShort();


	buff->position(0);
	const char* data = ((const char*)buff->array()) + HEADER_SIZE;

	return new BlockData(blockSize, fpos, used, nextfpos, data);
}

void BlockData::updateData(const char* ptr, int length) noexcept {
	this->used = length;

	Mem::memcpy(this->data, ptr, length);
}

} /* namespace alinous */


