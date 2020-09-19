/*
 * AlterModifyCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterModifyCommandLog.h"

#include "sql_ddl_alter_modify/AlterModifyCommand.h"

#include "engine_lock/WriteLockHandle.h"

#include "base/StackRelease.h"

#include "transaction/CdbTransactionManager.h"

#include "base/UnicodeString.h"

namespace codablecash {

AlterModifyCommandLog::AlterModifyCommandLog() : AbstractAlterCommandLog(AbstractTransactionLog::TRX_ALTER_MODIFY) {
	this->command = nullptr;
	this->defaultValueStr = nullptr;
}

AlterModifyCommandLog::~AlterModifyCommandLog() {
	delete this->command;
	delete this->defaultValueStr;
}

void AlterModifyCommandLog::setCommand(AlterModifyCommand* command) noexcept {
	this->command = command;
}

void AlterModifyCommandLog::setDefaultStr(UnicodeString* defaultValueStr) noexcept {
	this->defaultValueStr = defaultValueStr;
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
	WriteLockHandle* lockH = trxManager->databaseWriteLock(); __STP(lockH);

	trxManager->commitAlterTable(this);
}

void AlterModifyCommandLog::initCommandParam(VirtualMachine* vm) {
	this->command->interpret(vm, this);
}

} /* namespace codablecash */
