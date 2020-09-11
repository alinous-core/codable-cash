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
	CodeElement::checkNotNull(this->command);

	int total = sizeof(uint8_t);
	total += this->command->binarySize();

	return total;
}

void AlterDropPrimaryKeyCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_DROP_PRIMARY_KEY);
	this->command->toBinary(out);
}

void AlterDropPrimaryKeyCommandLog::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_DROP_PRIMARY_KEY);

	this->command = dynamic_cast<AlterDropPrimaryKeyCommand*>(element);
}

void AlterDropPrimaryKeyCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
