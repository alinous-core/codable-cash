/*
 * BtreeConfig.cpp
 *
 *  Created on: 2018/12/22
 *      Author: iizuka
 */

#include "btree/BtreeConfig.h"
#include "base_io/ByteBuffer.h"

namespace alinous {

BtreeConfig::BtreeConfig(const BtreeConfig* inst) {
	this->blockSize = inst->blockSize;
	this->nodeNumber = inst->nodeNumber;
}

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

BtreeConfig* BtreeConfig::fromBinary(ByteBuffer* in) {
	BtreeConfig* inst = new BtreeConfig();

	inst->blockSize = in->getLong();
	inst->nodeNumber = in->getLong();

	return inst;
}


} /* namespace alinous */

