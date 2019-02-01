/*
 * PoWGeneratedBlock.cpp
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#include "flash/PoWGeneratedBlock.h"
#include "PoWGeneratedBlockHeader.h"


namespace codablecash {

PoWGeneratedBlock::PoWGeneratedBlock() : AbstractFlashBlock(AbstractFlashBlock::BLK_POW_V0) {
}

PoWGeneratedBlock::PoWGeneratedBlock(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce)
					: AbstractFlashBlock(AbstractFlashBlock::BLK_POW_V0) {
	this->header = new PoWGeneratedBlockHeader(height, minerSig, nonce);
}

PoWGeneratedBlock::~PoWGeneratedBlock() {
	delete this->header;
}

int PoWGeneratedBlock::binarySize() const {
	return AbstractFlashBlock::binarySize();
}

void PoWGeneratedBlock::toBinary(ByteBuffer* out) const {
	AbstractFlashBlock::toBinary(out);
}

} /* namespace codablecash */
