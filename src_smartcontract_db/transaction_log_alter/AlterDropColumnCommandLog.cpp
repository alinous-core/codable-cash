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
	CodeElement::checkNotNull(this->command);

	int total = sizeof(uint8_t);
	total += this->command->binarySize();

	return total;
}

void AlterDropColumnCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_DROP_COLUMN);
	this->command->toBinary(out);
}

void AlterDropColumnCommandLog::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_DROP_COLUMN);

	this->command = dynamic_cast<AlterDropColumnCommand*>(element);
}

void AlterDropColumnCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */