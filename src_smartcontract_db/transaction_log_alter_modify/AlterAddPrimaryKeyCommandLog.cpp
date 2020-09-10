/*
 * AlterAddPrimaryKeyCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"

#include "sql_ddl_alter_modify/AlterAddPrimaryKeyCommand.h"

namespace codablecash {

AlterAddPrimaryKeyCommandLog::AlterAddPrimaryKeyCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_ADD_PRIMARY_KEY){
	this->command = nullptr;
}

AlterAddPrimaryKeyCommandLog::~AlterAddPrimaryKeyCommandLog() {
	delete this->command;
}

void AlterAddPrimaryKeyCommandLog::setCommand(AlterAddPrimaryKeyCommand* command) noexcept {
	this->command = command;
}

int AlterAddPrimaryKeyCommandLog::binarySize() const {
	int total = sizeof(uint8_t);

	return total;
}

void AlterAddPrimaryKeyCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterAddPrimaryKeyCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterAddPrimaryKeyCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
