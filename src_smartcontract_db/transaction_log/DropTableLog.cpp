/*
 * DropTableLog.cpp
 *
 *  Created on: 2020/10/09
 *      Author: iizuka
 */

#include "transaction_log/DropTableLog.h"
#include "transaction_log/AbstractTransactionLog.h"

#include "sql_join_parts/TableIdentifier.h"

namespace codablecash {

DropTableLog::DropTableLog() : AbstractDdlLog(AbstractTransactionLog::TRX_CREATE_TABLE) {
	this->tableId = nullptr;
}

DropTableLog::~DropTableLog() {
	delete this->tableId;
}

} /* namespace codablecash */
