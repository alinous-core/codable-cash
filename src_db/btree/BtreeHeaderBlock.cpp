/*
 * BtreeHeaderBlock.cpp
 *
 *  Created on: 2018/12/22
 *      Author: iizuka
 */

#include "btree/BtreeHeaderBlock.h"
#include "btree/BtreeConfig.h"

#include "base_io/ByteBuffer.h"

namespace alinous {

BtreeHeaderBlock::BtreeHeaderBlock() {
	this->config = nullptr;
	this->rootFpos = 0;
}

BtreeHeaderBlock::~BtreeHeaderBlock() {
	if(this->config != nullptr){
		delete this->config;
	}
}

int BtreeHeaderBlock::binarySize() {
	int size = this->config->binarySize();
	size += sizeof(this->rootFpos);
	return size;
}

void BtreeHeaderBlock::toBinary(ByteBuffer* out) {
	this->config->toBinary(out);
	out->putLong(this->rootFpos);
}

} /* namespace alinous */
