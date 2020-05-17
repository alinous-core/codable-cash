/*
 * AbstractTransactionLog.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "transaction_log/AbstractTransactionLog.h"

namespace codablecash {

AbstractTransactionLog::AbstractTransactionLog(uint8_t type) {
	this->type = type;
}

AbstractTransactionLog::~AbstractTransactionLog() {
}

} /* namespace codablecash */
