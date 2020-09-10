/*
 * AlterDropColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterDropColumnCommandLog.h"

#include "sql_ddl_alter/AlterDropColumnCommand.h"

namespace codablecash {

AlterDropColumnCommandLog::AlterDropColumnCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_DROP_COLUMN) {
	this->command = nullptr;
}

AlterDropColumnCommandLog::~AlterDropColumnCommandLog() {
	delete this->command;
}

void AlterDropColumnCommandLog::setCommand(AlterDropColumnCommand* command) noexcept {
	this->command = command;
}

int AlterDropColumnCommandLog::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterDropColumnCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterDropColumnCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterDropColumnCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
