/*
 * TicketGeneratedBlock.cpp
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#include "flash/TicketGeneratedBlock.h"
#include "flash/TicketGeneratedBlockHeader.h"

namespace codablecash {

TicketGeneratedBlock::TicketGeneratedBlock() : AbstractFlashBlock(AbstractFlashBlock::BLK_TICKET_V0) {

}

codablecash::TicketGeneratedBlock::TicketGeneratedBlock(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce)
				: AbstractFlashBlock(AbstractFlashBlock::BLK_TICKET_V0) {
	this->header = new TicketGeneratedBlockHeader(height, minerSig, nonce);
}


TicketGeneratedBlock::~TicketGeneratedBlock() {
	delete this->header;
}

int TicketGeneratedBlock::binarySize() const {
	return AbstractFlashBlock::binarySize();
}

void TicketGeneratedBlock::toBinary(ByteBuffer* out) const {
	AbstractFlashBlock::toBinary(out);
}

void TicketGeneratedBlock::fromBinary(ByteBuffer* in) {
	AbstractFlashBlock::fromBinary(in);
}

} /* namespace codablecash */
