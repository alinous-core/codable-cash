/*
 * AlterRenameTableCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"

#include "sql_ddl_alter_modify/AlterRenameTableCommand.h"

#include "engine_lock/WriteLockHandle.h"
#include "engine_lock/StackDbLockUnlocker.h"

#include "base/StackRelease.h"

#include "transaction/CdbTransactionManager.h"

namespace codablecash {

AlterRenameTableCommandLog::AlterRenameTableCommandLog() : AbstractAlterCommandLog(AbstractTransactionLog::TRX_ALTER_RENAME_TABLE) {
	this->command = nullptr;
}

AlterRenameTableCommandLog::~AlterRenameTableCommandLog() {
	delete this->command;
}

void AlterRenameTableCommandLog::setCommand(AlterRenameTableCommand* command) noexcept {
	this->command = command;
}

int AlterRenameTableCommandLog::binarySize() const {
	CodeElement::checkNotNull(this->command);

	int total = sizeof(uint8_t);

	total += AbstractAlterCommandLog::binarySize();
	total += this->command->binarySize();

	return total;;
}

void AlterRenameTableCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_RENAME_TABLE);

	AbstractAlterCommandLog::toBinary(out);
	this->command->toBinary(out);
}

void AlterRenameTableCommandLog::fromBinary(ByteBuffer* in) {
	AbstractAlterCommandLog::fromBinary(in);

	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_RENAME_TABLE);

	this->command = dynamic_cast<AlterRenameTableCommand*>(element);
}

void AlterRenameTableCommandLog::commit(CdbTransactionManager* trxManager) {
	WriteLockHandle* lockH = trxManager->databaseWriteLock();
	StackDbLockUnlocker unlocker(lockH);

	trxManager->commitAlterTable(this);
}

void AlterRenameTableCommandLog::initCommandParam(VirtualMachine* vm) {
	this->command->interpret(vm, this);
}

} /* namespace codablecash */
