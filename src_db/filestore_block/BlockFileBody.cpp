/*
 * BlockFileBody.cpp
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#include "filestore_block/BlockFileBody.h"

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

} /* namespace alinous */
