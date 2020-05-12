/*
 * AbstractDdlLog.cpp
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#include "transaction_log/AbstractDdlLog.h"

namespace codablecash {

AbstractDdlLog::AbstractDdlLog(uint8_t type) : AbstractTransactionLog(type) {

}

AbstractDdlLog::~AbstractDdlLog() {

}

} /* namespace codablecash */
