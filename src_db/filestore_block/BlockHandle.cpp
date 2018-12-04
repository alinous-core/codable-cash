/*
 * BlockHandle.cpp
 *
 *  Created on: 2018/11/20
 *      Author: iizuka
 */

#include "filestore_block/BlockHandle.h"

#include "filestore_block/BlockFileStore.h"
#include "filestore_block/BlockData.h"

namespace alinous {

BlockHandle::BlockHandle(BlockFileStore* store) noexcept {
	this->fpos = 0;

	this->store = store;
}

BlockHandle::~BlockHandle() {
}

void BlockHandle::loadBlock(uint64_t fpos) {
	this->fpos = fpos;

	BlockFileBody* body = this->store->getBody();



}


} /* namespace alinous */

