/*
 * BlockHandle.cpp
 *
 *  Created on: 2018/11/20
 *      Author: iizuka
 */

#include "filestore_block/BlockHandle.h"

#include "filestore_block/BlockFileStore.h"
#include "filestore_block/BlockFileBody.h"
#include "filestore_block/BlockFileHeader.h"
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


static void __copy(BlockData* block, const char* data, RawArrayPrimitive<char>* bytes){
	int maxLoop = block->getUsed();
	for(int i = 0; i != maxLoop; ++i){
		bytes->addElement(data[i]);
	}
}

void BlockHandle::loadBlock(uint64_t fpos) {
	this->fpos = fpos;

	BlockFileBody* body = this->store->getBody();
	RawArrayPrimitive<char> bytes(512);

	BlockData* block = nullptr;
	do{
		block = body->loadBlock(fpos);
		StackRelease<BlockData> _stBlock(block);

		const char* data = block->getData();


		__copy(block, data, &bytes);

		fpos = block->getNextfpos();
	}
	while(fpos != 0);


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
	uint64_t nextPos = this->fpos;
	uint64_t lastBlockPos = 0;
	do{
		block = body->loadBlock(nextPos);
		StackRelease<BlockData> _stBlock(block);

		int writeLength = remain < blockDataLength ? remain : blockDataLength;

		block->updateData(ptr, writeLength);
		body->writeBlock(block);

		remain -= writeLength;
		ptr += writeLength;

		lastBlockPos = block->getCurrentfPos();
		nextPos = block->getNextfpos();
	}
	while(remain > 0 && nextPos != 0);

	// alloc
	BlockFileHeader* header = this->store->getHeader();

	BlockData* lastblock = nullptr;
	while(remain > 0){
		uint64_t newfpos = header->alloc() * body->getBlockSize();

		{
			lastblock = body->loadBlock(lastBlockPos);
			StackRelease<BlockData> _stLastBlock(lastblock);

			lastblock->updateNextFpos(newfpos);
			body->writeBlock(lastblock);
		}

		block = BlockData::createNewBlock(body->getBlockSize(), newfpos, 0, 0);
		StackRelease<BlockData> _stBlock(block);

		int writeLength = remain < blockDataLength ? remain : blockDataLength;
		block->updateData(ptr, writeLength);
		body->writeBlock(block);

		remain -= writeLength;
		ptr += writeLength;
		lastBlockPos = block->getCurrentfPos();
	}

	// dispose
	if(nextPos != 0){
		block = body->loadBlock(lastBlockPos);
		StackRelease<BlockData> _stBlock(block);

		block->updateNextFpos(0);
		body->writeBlock(block);

		removeBlocks(nextPos);
	}

}

void BlockHandle::removeBlocks(uint64_t fpos) {
	uint64_t nextPos = fpos;
	BlockFileBody* body = this->store->getBody();
	BlockFileHeader* header = this->store->getHeader();

	do{
		BlockData* block = body->loadBlock(nextPos);
		StackRelease<BlockData> _stBlock(block);

		uint64_t curfpos = block->getCurrentfPos();
		nextPos = block->getNextfpos();

		header->remove(curfpos);

	}
	while(nextPos != 0);

	header->sync(false);
}

void BlockHandle::initOnAlloc(uint64_t fpos, int size) noexcept {
	this->fpos = fpos;
	this->buffer = ByteBuffer::allocateWithEndian(size, true);
}

} /* namespace alinous */

