/*
 * BtreeConfig.cpp
 *
 *  Created on: 2018/12/22
 *      Author: iizuka
 */

#include "btree/BtreeConfig.h"
#include "base_io/ByteBuffer.h"

namespace alinous {

BtreeConfig::BtreeConfig() {
	this->blockSize = 256;
	this->nodeNumber = 8;
}

BtreeConfig::~BtreeConfig() {
}

int BtreeConfig::binarySize() {
	return sizeof(this->blockSize) + sizeof(this->nodeNumber);
}

void BtreeConfig::toBinary(ByteBuffer* out) {
	out->putLong(this->blockSize);
	out->putLong(this->nodeNumber);
}

} /* namespace alinous */
