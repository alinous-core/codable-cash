/*
 * TicketGeneratedBlockHeader.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef FLASH_TICKETGENERATEDBLOCKHEADER_H_
#define FLASH_TICKETGENERATEDBLOCKHEADER_H_

#include "AbstractFlashBlockHeader.h"

namespace codablecash {

class TicketGeneratedBlockHeader : public AbstractFlashBlockHeader {
public:
	TicketGeneratedBlockHeader(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce);
	virtual ~TicketGeneratedBlockHeader();
};

} /* namespace codablecash */

#endif /* FLASH_TICKETGENERATEDBLOCKHEADER_H_ */
