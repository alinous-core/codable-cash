/*
 * AlterDropIndexCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterDropIndexCommandLog.h"

namespace codablecash {

AlterDropIndexCommandLog::AlterDropIndexCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_DROP_INDEX) {

}

AlterDropIndexCommandLog::~AlterDropIndexCommandLog() {

}

} /* namespace codablecash */
