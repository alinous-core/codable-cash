/*
 * AbstractAlterCommandLog.cpp
 *
 *  Created on: 2020/09/16
 *      Author: iizuka
 */

#include "transaction_log_alter/AbstractAlterCommandLog.h"

#include "sql_join_parts/TableIdentifier.h"

namespace codablecash {

AbstractAlterCommandLog::AbstractAlterCommandLog(uint8_t type) : AbstractDdlLog(type) {
	this->tableId = nullptr;
}

AbstractAlterCommandLog::~AbstractAlterCommandLog() {
	delete this->tableId;
}

void AbstractAlterCommandLog::setTableIdentifier(const TableIdentifier* tableId) noexcept {
	this->tableId = new TableIdentifier(*tableId);
}


} /* namespace codablecash */
