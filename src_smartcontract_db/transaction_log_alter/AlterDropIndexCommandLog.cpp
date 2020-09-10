/*
 * AlterDropIndexCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterDropIndexCommandLog.h"

#include "sql_ddl_alter/AlterDropIndexCommand.h"

namespace codablecash {

AlterDropIndexCommandLog::AlterDropIndexCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_DROP_INDEX) {
	this->command = nullptr;
}

AlterDropIndexCommandLog::~AlterDropIndexCommandLog() {
	delete this->command;
}

void AlterDropIndexCommandLog::setCommand(AlterDropIndexCommand* command) noexcept {
	this->command = command;
}

int AlterDropIndexCommandLog::binarySize() const {
	int total = sizeof(uint8_t);

	return total;
}

void AlterDropIndexCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterDropIndexCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterDropIndexCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
