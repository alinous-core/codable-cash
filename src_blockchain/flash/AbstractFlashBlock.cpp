/*
 * AbstractFlashBlock.cpp
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#include "flash/AbstractFlashBlock.h"

#include "AbstractFlashBlockHeader.h"
#include "bc_base/AbstractTransaction.h"
#include "MinerSignature.h"

namespace codablecash {

AbstractFlashBlock::AbstractFlashBlock(uint8_t type) {
	this->type = type;
	this->header = nullptr;
}

AbstractFlashBlock::~AbstractFlashBlock() {
	this->list.deleteElements();
}

int AbstractFlashBlock::binarySize() const {
	int total = sizeof(this->type);
	total += this->header->binarySize();

	// FIXME
}

void AbstractFlashBlock::toBinary(ByteBuffer* out) const {
	// FIXME
}

} /* namespace codablecash */
