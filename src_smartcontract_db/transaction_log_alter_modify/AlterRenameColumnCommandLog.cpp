/*
 * AlterRenameColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterRenameColumnCommandLog.h"

#include "sql_ddl_alter_modify/AlterRenameColumnCommand.h"

namespace codablecash {

AlterRenameColumnCommandLog::AlterRenameColumnCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_RENAME_COLUMN) {
	this->command = nullptr;
}

AlterRenameColumnCommandLog::~AlterRenameColumnCommandLog() {
	delete this->command;
}

void AlterRenameColumnCommandLog::setCommand(AlterRenameColumnCommand* command) noexcept {
	this->command = command;
}

int AlterRenameColumnCommandLog::binarySize() const {
	CodeElement::checkNotNull(this->command);

	int total = sizeof(uint8_t);
	total += this->command->binarySize();

	return total;
}

void AlterRenameColumnCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_RENAME_COLUMN);
	this->command->toBinary(out);
}

void AlterRenameColumnCommandLog::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_RENAME_COLUMN);

	this->command = dynamic_cast<AlterRenameColumnCommand*>(element);
}

void AlterRenameColumnCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
