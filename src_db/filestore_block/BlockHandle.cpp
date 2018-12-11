/*
 * BlockHandle.cpp
 *
 *  Created on: 2018/11/20
 *      Author: iizuka
 */

#include "filestore_block/BlockHandle.h"

#include "filestore_block/BlockFileStore.h"
#include "filestore_block/BlockFileBody.h"
#include "filestore_block/BlockData.h"

#include "base/RawArrayPrimitive.h"
#include "base/StackRelease.h"

#include "base_io/ByteBuffer.h"

namespace alinous {

BlockHandle::BlockHandle(BlockFileStore* store) noexcept {
	this->fpos = 0;
	this->store = store;
	this->buffer = nullptr;
}

BlockHandle::~BlockHandle() {
	if(this->buffer != nullptr){
		delete this->buffer;
	}
}

void BlockHandle::loadBlock(uint64_t fpos) {
	this->fpos = fpos;

	BlockFileBody* body = this->store->getBody();
	RawArrayPrimitive<char> bytes(512);

	BlockData* block = nullptr;
	uint64_t nextPos;
	do{
		block = body->loadBlock(fpos);
		StackRelease<BlockData> _stBlock(block);

		const char* data = block->getData();


		int maxLoop = block->getUsed();
		for(int i = 0; i != maxLoop; ++i){
			bytes.addElement(data[i]);
		}

		nextPos = block->getNextfpos();
	}
	while(nextPos != 0);


	const char* _data = bytes.root;
	int size = bytes.size();

	this->buffer = ByteBuffer::wrapWithEndian((const uint8_t*)_data, size, true);
}

int BlockHandle::size() noexcept {
	return this->buffer->capacity();
}

void BlockHandle::write(const char* bytes, int length) {
	if(this->buffer != nullptr){
		delete this->buffer;
	}

	// buffer
	this->buffer = ByteBuffer::wrapWithEndian((const uint8_t*)bytes, length, true);
	this->buffer->position(0);

	// storage data
	BlockData* block;
	BlockFileBody* body = this->store->getBody();
	const char* ptr = bytes;
	int blockDataLength = body->getBlockSize() - BlockData::HEADER_SIZE;
	int remain = length;
	do{
		block = body->loadBlock(fpos);
		StackRelease<BlockData> _stBlock(block);

		int writeLength = remain < blockDataLength ? remain : blockDataLength;

		block->updateData(ptr, writeLength);
		body->writeBlock(block);

		remain -= writeLength;
		ptr += writeLength;

	}
	while(remain > 0 && block->getNextfpos() != 0);

	// alloc

	// dispose

}

void BlockHandle::initOnAlloc(uint64_t fpos, int size) noexcept {
	this->fpos = fpos;
	this->buffer = ByteBuffer::allocateWithEndian(size, true);
}

} /* namespace alinous */

