/*
 * TicketGeneratedBlockHeader.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "TicketGeneratedBlockHeader.h"

namespace codablecash {

TicketGeneratedBlockHeader::TicketGeneratedBlockHeader() : AbstractFlashBlockHeader(AbstractFlashBlockHeader::BLKH_TICKET_V0) {
}


TicketGeneratedBlockHeader::TicketGeneratedBlockHeader(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce)
								: AbstractFlashBlockHeader(AbstractFlashBlockHeader::BLKH_TICKET_V0, height, minerSig, nonce) {
}

TicketGeneratedBlockHeader::~TicketGeneratedBlockHeader() {
}

int TicketGeneratedBlockHeader::binarySize() const {
	return AbstractFlashBlockHeader::binarySize();
}

void TicketGeneratedBlockHeader::toBinary(ByteBuffer* out) const {
	AbstractFlashBlockHeader::toBinary(out);
}

void TicketGeneratedBlockHeader::fromBinary(ByteBuffer* in) {
	AbstractFlashBlockHeader::fromBinary(in);
}

} /* namespace codablecash */
