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

class TicketGeneratedBlock: public AbstractFlashBlock {
public:
	TicketGeneratedBlock();
	virtual ~TicketGeneratedBlock();
};

} /* namespace codablecash */

#endif /* FLASH_TICKETGENERATEDBLOCK_H_ */
