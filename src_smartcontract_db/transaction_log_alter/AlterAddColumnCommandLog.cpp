/*
 * AlterAddColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterAddColumnCommandLog.h"

namespace codablecash {

AlterAddColumnCommandLog::AlterAddColumnCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_ADD_COLUMN) {

}

AlterAddColumnCommandLog::~AlterAddColumnCommandLog() {

}

} /* namespace codablecash */
