/*
 * AlterAddColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterAddColumnCommandLog.h"

#include "sql_ddl_alter/AlterAddColumnCommand.h"

namespace codablecash {

AlterAddColumnCommandLog::AlterAddColumnCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_ADD_COLUMN) {
	this->command = nullptr;
}

AlterAddColumnCommandLog::~AlterAddColumnCommandLog() {
	delete this->command;
}

void AlterAddColumnCommandLog::setCommand(AlterAddColumnCommand* command) noexcept {
	this->command = command;
}

int AlterAddColumnCommandLog::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterAddColumnCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterAddColumnCommandLog::fromBinary(ByteBuffer* in) {

}

void AlterAddColumnCommandLog::commit(CdbTransactionManager* trxManager) {
}


} /* namespace codablecash */
