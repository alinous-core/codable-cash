/*
 * AlterDropColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterDropColumnCommandLog.h"

namespace codablecash {

AlterDropColumnCommandLog::AlterDropColumnCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_DROP_COLUMN) {

}

AlterDropColumnCommandLog::~AlterDropColumnCommandLog() {

}

} /* namespace codablecash */
