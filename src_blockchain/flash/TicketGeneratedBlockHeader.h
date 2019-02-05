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
private:
	friend class AbstractFlashBlockHeader;
	TicketGeneratedBlockHeader();
public:
	TicketGeneratedBlockHeader(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce);
	virtual ~TicketGeneratedBlockHeader();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace codablecash */

#endif /* FLASH_TICKETGENERATEDBLOCKHEADER_H_ */
