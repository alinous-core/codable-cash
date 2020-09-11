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
	CodeElement::checkNotNull(this->command);

	int total = sizeof(uint8_t);
	total += this->command->binarySize();

	return total;
}

void AlterModifyCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_MODIFY);
	this->command->toBinary(out);
}

void AlterModifyCommandLog::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_MODIFY);

	this->command = dynamic_cast<AlterModifyCommand*>(element);
}

void AlterModifyCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
