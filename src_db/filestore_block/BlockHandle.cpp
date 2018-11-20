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
	this->start = 0;
	this->current = 0;
	this->data = nullptr;

	this->store = store;
}

BlockHandle::~BlockHandle() {
	if(this->data != nullptr){
		delete this->data;
	}
}

} /* namespace alinous */
