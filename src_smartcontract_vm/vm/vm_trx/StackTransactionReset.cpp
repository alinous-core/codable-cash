/*
 * StackTransactionReset.cpp
 *
 *  Created on: 2020/05/24
 *      Author: iizuka
 */

#include "vm/vm_trx/StackTransactionReset.h"
#include "vm/vm_trx/VmTransactionHandler.h"

namespace alinous {

StackTransactionReset::StackTransactionReset(VmTransactionHandler* handler) {
	this->handler = handler;
}

StackTransactionReset::~StackTransactionReset() {
	this->handler->reset();
}

} /* namespace alinous */
