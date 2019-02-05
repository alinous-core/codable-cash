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
#include "filestore_block/exceptions.h"

#include "flash/PoWGeneratedBlockHeader.h"
#include "flash/TicketGeneratedBlockHeader.h"

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
	int total = sizeof(uint16_t) + sizeof(this->height);
	total += this->minerSig->binarySize();
	total += this->nonce->binarySize();

	return total;
}

void AbstractFlashBlockHeader::toBinary(ByteBuffer* out) const {
	out->putShort(this->kind);
	out->putLong(this->height);
	this->minerSig->toBinary(out);
	this->nonce->toBinary(out);
}

void AbstractFlashBlockHeader::fromBinary(ByteBuffer* in) {
	this->height = in->getLong();

	this->minerSig = MinerSignature::fromBinary(in);
	this->nonce = Nonce::fromBinary(in);
}

AbstractFlashBlockHeader* AbstractFlashBlockHeader::createFromBinary(ByteBuffer* in) {
	int kind = in->getShort();

	AbstractFlashBlockHeader* header = nullptr;
	switch (kind) {
		case AbstractFlashBlockHeader::BLKH_POW_V0:
			header = new PoWGeneratedBlockHeader();
			break;
		case AbstractFlashBlockHeader::BLKH_TICKET_V0:
			header = new TicketGeneratedBlockHeader();
			break;
		default:
			throw new BinaryFormatException(L"Format of Blockchain header type is wrong", __FILE__, __LINE__);
	}

	header->fromBinary(in);
	return header;
}

} /* namespace codablecash */
