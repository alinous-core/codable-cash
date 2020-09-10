/*
 * AlterDropPrimaryKeyCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"

namespace codablecash {

AlterDropPrimaryKeyCommandLog::AlterDropPrimaryKeyCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_DROP_PRIMARY_KEY) {

}

AlterDropPrimaryKeyCommandLog::~AlterDropPrimaryKeyCommandLog() {

}

} /* namespace codablecash */
