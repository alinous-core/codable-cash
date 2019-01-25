/*
 * TicketTransaction.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "TicketTransaction.h"

#include "flash_pow/Nonce.h"

namespace codablecash {

TicketTransaction::TicketTransaction() : AbstractTransaction(AbstractTransaction::TYPE_TICKET) {
	this->fheight = 0;
	this->nonce = nullptr;
}

TicketTransaction::~TicketTransaction() {
	delete this->nonce;
}

} /* namespace codablecash */
