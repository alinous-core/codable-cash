/*
 * PoWGeneratedBlockHeader.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "PoWGeneratedBlockHeader.h"

#include "flash_pow/Nonce.h"

namespace codablecash {

PoWGeneratedBlockHeader::PoWGeneratedBlockHeader(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce)
					: AbstractFlashBlockHeader(height, minerSig, nonce) {

}

PoWGeneratedBlockHeader::~PoWGeneratedBlockHeader() {

}

} /* namespace codablecash */
