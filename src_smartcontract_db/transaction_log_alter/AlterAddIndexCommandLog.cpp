/*
 * AlterAddIndexCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterAddIndexCommandLog.h"

namespace codablecash {

AlterAddIndexCommandLog::AlterAddIndexCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_ADD_INDEX) {

}

AlterAddIndexCommandLog::~AlterAddIndexCommandLog() {

}

} /* namespace codablecash */
