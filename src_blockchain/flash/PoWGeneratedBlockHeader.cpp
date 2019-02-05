/*
 * PoWGeneratedBlockHeader.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "PoWGeneratedBlockHeader.h"

#include "flash_pow/Nonce.h"

namespace codablecash {

PoWGeneratedBlockHeader::PoWGeneratedBlockHeader() : AbstractFlashBlockHeader(AbstractFlashBlockHeader::BLKH_POW_V0) {
}

PoWGeneratedBlockHeader::PoWGeneratedBlockHeader(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce)
					: AbstractFlashBlockHeader(AbstractFlashBlockHeader::BLKH_POW_V0, height, minerSig, nonce) {

}

PoWGeneratedBlockHeader::~PoWGeneratedBlockHeader() {

}

int PoWGeneratedBlockHeader::binarySize() const {
	return AbstractFlashBlockHeader::binarySize();
}

void PoWGeneratedBlockHeader::toBinary(ByteBuffer* out) const {
	AbstractFlashBlockHeader::toBinary(out);
}

void PoWGeneratedBlockHeader::fromBinary(ByteBuffer* in) {
	AbstractFlashBlockHeader::fromBinary(in);
}

} /* namespace codablecash */
