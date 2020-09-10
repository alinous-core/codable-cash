/*
 * AlterModifyCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterModifyCommandLog.h"

#include "sql_ddl_alter_modify/AlterModifyCommand.h"

namespace codablecash {

AlterModifyCommandLog::AlterModifyCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_MODIFY) {
	this->command = nullptr;
}

AlterModifyCommandLog::~AlterModifyCommandLog() {
	delete this->command;
}

void AlterModifyCommandLog::setCommand(AlterModifyCommand* command) noexcept {
	this->command = command;
}

int AlterModifyCommandLog::binarySize() const {
	int total = sizeof(uint8_t);

	return total;
}

void AlterModifyCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterModifyCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterModifyCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
