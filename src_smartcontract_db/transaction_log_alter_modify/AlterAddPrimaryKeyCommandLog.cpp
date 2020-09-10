/*
 * AlterAddPrimaryKeyCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"

namespace codablecash {

AlterAddPrimaryKeyCommandLog::AlterAddPrimaryKeyCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_ADD_PRIMARY_KEY){

}

AlterAddPrimaryKeyCommandLog::~AlterAddPrimaryKeyCommandLog() {

}

} /* namespace codablecash */
