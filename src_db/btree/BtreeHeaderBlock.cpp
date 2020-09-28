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

BtreeHeaderBlock::BtreeHeaderBlock(const BtreeHeaderBlock& inst) {
	this->config = inst.config != nullptr ? dynamic_cast<BtreeConfig*>(inst.config->copyData()) : nullptr;
	this->rootFpos = inst.rootFpos;
}

BtreeHeaderBlock::BtreeHeaderBlock() {
	this->config = nullptr;
	this->rootFpos = 0;
}

BtreeHeaderBlock::~BtreeHeaderBlock() {
	if(this->config != nullptr){
		delete this->config;
	}
}

void BtreeHeaderBlock::setConfig(const BtreeConfig* config) noexcept {
	this->config = new BtreeConfig(config);
}

int BtreeHeaderBlock::binarySize() const {
	int size = this->config->binarySize();
	size += sizeof(this->rootFpos);
	return size;
}

void BtreeHeaderBlock::toBinary(ByteBuffer* out) const {
	this->config->toBinary(out);
	out->putLong(this->rootFpos);
}

BtreeHeaderBlock* BtreeHeaderBlock::fromBinary(ByteBuffer* in){
	BtreeHeaderBlock* header = new BtreeHeaderBlock();

	header->config = BtreeConfig::fromBinary(in);
	header->rootFpos = in->getLong();

	return header;
}

IBlockObject* BtreeHeaderBlock::copyData() const noexcept {
	return new BtreeHeaderBlock(*this);
}

} /* namespace alinous */
