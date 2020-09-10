/*
 * AlterRenameColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterRenameColumnCommandLog.h"

namespace codablecash {

AlterRenameColumnCommandLog::AlterRenameColumnCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_RENAME_COLUMN) {

}

AlterRenameColumnCommandLog::~AlterRenameColumnCommandLog() {

}

} /* namespace codablecash */
