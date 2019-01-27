/*
 * AbstractFlashBlockHeader.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "AbstractFlashBlockHeader.h"

#include "flash_pow/Nonce.h"
#include "MinerSignature.h"


namespace codablecash {

AbstractFlashBlockHeader::AbstractFlashBlockHeader(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce) {
	this->height = height;
	this->minerSig = new MinerSignature(*minerSig);
	this->nonce = new Nonce(*nonce);
}

AbstractFlashBlockHeader::~AbstractFlashBlockHeader() {
	delete this->minerSig;
	delete this->nonce;
}

} /* namespace codablecash */
