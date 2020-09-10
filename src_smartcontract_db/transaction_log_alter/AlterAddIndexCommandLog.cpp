/*
 * AlterAddIndexCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterAddIndexCommandLog.h"

#include "sql_ddl_alter/AlterAddIndexCommand.h"

namespace codablecash {

AlterAddIndexCommandLog::AlterAddIndexCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_ADD_INDEX) {
	this->command = nullptr;
}

AlterAddIndexCommandLog::~AlterAddIndexCommandLog() {
	delete this->command;
}

void AlterAddIndexCommandLog::setCommand(AlterAddIndexCommand* command) noexcept {
	this->command = command;
}

int AlterAddIndexCommandLog::binarySize() const {
	int total = sizeof(uint8_t);

	return total;
}

void AlterAddIndexCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterAddIndexCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterAddIndexCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
