/*
 * AlterModifyCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterModifyCommandLog.h"

namespace codablecash {

AlterModifyCommandLog::AlterModifyCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_MODIFY) {

}

AlterModifyCommandLog::~AlterModifyCommandLog() {

}

} /* namespace codablecash */
