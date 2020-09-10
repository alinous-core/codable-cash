/*
 * AlterRenameTableCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"

#include "sql_ddl_alter_modify/AlterRenameTableCommand.h"

namespace codablecash {

AlterRenameTableCommandLog::AlterRenameTableCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_RENAME_TABLE) {
	this->command = nullptr;
}

AlterRenameTableCommandLog::~AlterRenameTableCommandLog() {
	delete this->command;
}

void AlterRenameTableCommandLog::setCommand(AlterRenameTableCommand* command) noexcept {
	this->command = command;
}

int AlterRenameTableCommandLog::binarySize() const {
	int total = sizeof(uint8_t);

	return total;
}

void AlterRenameTableCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterRenameTableCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterRenameTableCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
