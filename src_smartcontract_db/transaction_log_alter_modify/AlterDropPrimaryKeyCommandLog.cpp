/*
 * AlterDropPrimaryKeyCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"

#include "sql_ddl_alter_modify/AlterDropPrimaryKeyCommand.h"

namespace codablecash {

AlterDropPrimaryKeyCommandLog::AlterDropPrimaryKeyCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_DROP_PRIMARY_KEY) {
	this->command = nullptr;
}

AlterDropPrimaryKeyCommandLog::~AlterDropPrimaryKeyCommandLog() {
	delete this->command;
}

void AlterDropPrimaryKeyCommandLog::setCommand(AlterDropPrimaryKeyCommand* command) noexcept {
	this->command = command;
}

int AlterDropPrimaryKeyCommandLog::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterDropPrimaryKeyCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterDropPrimaryKeyCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterDropPrimaryKeyCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
