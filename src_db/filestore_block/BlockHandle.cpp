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

	BlockData* block;
	do{
		block = body->loadBlock(fpos);
		StackRelease<BlockData> _stBlock(block);

		const char* data = block->getData();


		int maxLoop = block->getUsed();
		for(int i = 0; i != maxLoop; ++i){
			bytes.addElement(data[i]);
		}
	}
	while(block->getNextfpos() != 0);


	const char* _data = bytes.root;
	int size = bytes.size();

	this->buffer = ByteBuffer::wrapWithEndian((const uint8_t*)_data, size, true);
}

int BlockHandle::size() noexcept {
	return this->buffer->capacity();
}

void BlockHandle::initOnAlloc(uint64_t fpos, int size) noexcept {
	this->fpos = fpos;
	this->buffer = ByteBuffer::allocateWithEndian(size, true);
}

} /* namespace alinous */

