/*
 * TicketGeneratedBlock.cpp
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#include "flash/TicketGeneratedBlock.h"

namespace codablecash {

TicketGeneratedBlock::TicketGeneratedBlock() : AbstractFlashBlock(AbstractFlashBlock::BLK_TICKET_V0) {

}

TicketGeneratedBlock::~TicketGeneratedBlock() {
}

int TicketGeneratedBlock::binarySize() const {
	return AbstractFlashBlock::binarySize();
}

void TicketGeneratedBlock::toBinary(ByteBuffer* out) const {
	AbstractFlashBlock::toBinary(out);
}

} /* namespace codablecash */
