/*
 * AbstractFlashBlockHeader.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "AbstractFlashBlockHeader.h"

#include "flash_pow/Nonce.h"
#include "MinerSignature.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

AbstractFlashBlockHeader::AbstractFlashBlockHeader(int kind) {
	this->kind = kind;
	this->height =0;
	this->minerSig = nullptr;
	this->nonce = nullptr;
}

AbstractFlashBlockHeader::AbstractFlashBlockHeader(int kind, uint64_t height, const MinerSignature* minerSig, const Nonce* nonce) {
	this->kind = kind;
	this->height = height;
	this->minerSig = new MinerSignature(*minerSig);
	this->nonce = new Nonce(*nonce);
}

AbstractFlashBlockHeader::~AbstractFlashBlockHeader() {
	delete this->minerSig;
	delete this->nonce;
}

int AbstractFlashBlockHeader::binarySize() const {
	int total = sizeof(uint8_t) + sizeof(this->height);
	total += this->minerSig->binarySize();
	total += this->nonce->binarySize();

	return total;
}

void AbstractFlashBlockHeader::toBinary(ByteBuffer* out) const {
	out->putLong(this->height);
	this->minerSig->toBinary(out);
	this->nonce->toBinary(out);
}

} /* namespace codablecash */
