/*
 * AlterRenameTableCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"

namespace codablecash {

AlterRenameTableCommandLog::AlterRenameTableCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_RENAME_TABLE) {

}

AlterRenameTableCommandLog::~AlterRenameTableCommandLog() {

}

} /* namespace codablecash */
