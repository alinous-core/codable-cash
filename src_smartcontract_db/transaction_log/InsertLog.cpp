/*
 * InsertLog.cpp
 *
 *  Created on: 2020/05/28
 *      Author: iizuka
 */

#include "transaction_log/InsertLog.h"

namespace codablecash {

InsertLog::InsertLog() : AbstractTransactionLog(AbstractTransactionLog::TRX_INSERT) {

}

InsertLog::~InsertLog() {

}

} /* namespace codablecash */
