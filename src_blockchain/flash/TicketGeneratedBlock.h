/*
 * TicketGeneratedBlock.h
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#ifndef FLASH_TICKETGENERATEDBLOCK_H_
#define FLASH_TICKETGENERATEDBLOCK_H_

#include "flash/AbstractFlashBlock.h"

namespace codablecash {

class MinerSignature;
class Nonce;

class TicketGeneratedBlock: public AbstractFlashBlock {
private:
	friend class AbstractFlashBlock;

	TicketGeneratedBlock();

public:
	TicketGeneratedBlock(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce);
	virtual ~TicketGeneratedBlock();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace codablecash */

#endif /* FLASH_TICKETGENERATEDBLOCK_H_ */
