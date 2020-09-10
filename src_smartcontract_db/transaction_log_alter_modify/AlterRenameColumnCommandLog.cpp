/*
 * AlterRenameColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterRenameColumnCommandLog.h"

#include "sql_ddl_alter_modify/AlterRenameColumnCommand.h"

namespace codablecash {

AlterRenameColumnCommandLog::AlterRenameColumnCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_RENAME_COLUMN) {
	this->command = nullptr;
}

AlterRenameColumnCommandLog::~AlterRenameColumnCommandLog() {
	delete this->command;
}

void AlterRenameColumnCommandLog::setCommand(AlterRenameColumnCommand* command) noexcept {
	this->command = command;
}

int AlterRenameColumnCommandLog::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterRenameColumnCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterRenameColumnCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterRenameColumnCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
