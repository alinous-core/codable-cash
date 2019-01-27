/*
 * TicketGeneratedBlockHeader.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "TicketGeneratedBlockHeader.h"

namespace codablecash {

TicketGeneratedBlockHeader::TicketGeneratedBlockHeader(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce)
								: AbstractFlashBlockHeader(height, minerSig, nonce) {
}

TicketGeneratedBlockHeader::~TicketGeneratedBlockHeader() {
}

} /* namespace codablecash */
