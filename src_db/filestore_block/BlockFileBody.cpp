/*
 * BlockFileBody.cpp
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#include "filestore_block/BlockFileBody.h"
#include "filestore_block/BlockData.h"

#include "base_io/ReverseByteBuffer.h"
#include "random_access_file/RandomAccessFile.h"

#include "base/StackRelease.h"

#include "debug/debugMacros.h"

namespace alinous {

BlockFileBody::BlockFileBody(RandomAccessFile* file, uint64_t blockSize) noexcept{
	this->file = file;
	this->blockSize = blockSize;
}

BlockFileBody::~BlockFileBody() {
}

void BlockFileBody::createStore(bool del, uint64_t blockSize) {
	this->blockSize = blockSize;
}

uint64_t BlockFileBody::alloc(uint64_t fpos, uint64_t used, uint64_t nextfpos) {
	BlockData* data = BlockData::createNewBlock(this->blockSize, fpos, used, nextfpos);
	StackRelease<BlockData> _st_data(data);

	writeBlock(data);
	this->file->sync(false);

	return 0;
}

void BlockFileBody::writeBlock(BlockData* data) {
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(this->blockSize, true);
	StackRelease<ByteBuffer> _st_buff(buff);

	buff->putLong(data->getCurrentfPos());
	buff->putLong(data->getNextfpos());
	buff->putShort(data->getUsed());

	int length = buff->position();
	buff->position(0);

	int fpos = data->getCurrentfPos();
	fpos += this->file->write(fpos, (const char*)buff->array(), length);

	length = data->getUsed();
	this->file->write(fpos, data->getData(), length);
}

BlockData* BlockFileBody::loadBlock(uint64_t fpos) {
	char* buff = new char[this->blockSize];
	StackArrayRelease<char> _st_buff(buff);

	this->file->read(fpos, buff, this->blockSize);

	return BlockData::fromBinary(this->blockSize, buff, this->blockSize);
}

void BlockFileBody::sync(bool fileSync) {
	this->file->sync(fileSync);
}


} /* namespace alinous */

