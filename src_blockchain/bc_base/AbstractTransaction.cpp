/*
 * AbstractTransaction.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/AbstractTransaction.h"
#include "bc_base/Transaction.h"
#include "base_io/ByteBuffer.h"
#include "bc/exceptions.h"

namespace codablecash {

AbstractTransaction::AbstractTransaction(int type) {
	this->type = type;
}

AbstractTransaction::AbstractTransaction(const AbstractTransaction& inst) {
	this->type = inst.type;
}

AbstractTransaction::~AbstractTransaction() {
}

AbstractTransaction* AbstractTransaction::fromBinary(ByteBuffer* in) {
	char type = in->get();

	AbstractTransaction* retValue = nullptr;
	switch(type){
	case AbstractTransaction::TYPE_SEND_BALANCE:
		retValue = Transaction::fromBinary(in);
		break;
	default:
		throw new MulformattedTransactionBinaryException(L"Transaction type is wrong.", __FILE__, __LINE__);
	}

	return retValue;
}

} /* namespace codablecash */
