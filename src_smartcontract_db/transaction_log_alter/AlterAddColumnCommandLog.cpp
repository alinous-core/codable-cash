/*
 * AlterAddColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterAddColumnCommandLog.h"

#include "sql_ddl_alter/AlterAddColumnCommand.h"

#include "sc/CodeElement.h"

namespace codablecash {

AlterAddColumnCommandLog::AlterAddColumnCommandLog() : AbstractAlterCommandLog(AbstractTransactionLog::TRX_ALTER_ADD_COLUMN) {
	this->command = nullptr;
}

AlterAddColumnCommandLog::~AlterAddColumnCommandLog() {
	delete this->command;
}

void AlterAddColumnCommandLog::setCommand(AlterAddColumnCommand* command) noexcept {
	this->command = command;
}

int AlterAddColumnCommandLog::binarySize() const {
	CodeElement::checkNotNull(this->command);

	int total = sizeof(uint8_t);
	total += this->command->binarySize();

	return total;
}

void AlterAddColumnCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_ADD_COLUMN);
	this->command->toBinary(out);
}

void AlterAddColumnCommandLog::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_ADD_COLUMN);

	this->command = dynamic_cast<AlterAddColumnCommand*>(element);
}

void AlterAddColumnCommandLog::commit(CdbTransactionManager* trxManager) {
}


} /* namespace codablecash */
