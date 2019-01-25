/*
 * TicketTransaction.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef BC_BASE_TICKETTRANSACTION_H_
#define BC_BASE_TICKETTRANSACTION_H_

#include <cstdint>
#include "AbstractTransaction.h"

namespace codablecash {

class Nonce;

class TicketTransaction : public AbstractTransaction {
public:
	TicketTransaction();
	virtual ~TicketTransaction();

private:
	Nonce* nonce;
	uint64_t fheight;

};

} /* namespace codablecash */

#endif /* BC_BASE_TICKETTRANSACTION_H_ */
