/*
 * AlterDropIndexCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "trx/transaction_log_alter/AlterDropIndexCommandLog.h"

#include "sql_ddl_alter/AlterDropIndexCommand.h"

#include "trx/transaction/CdbTransactionManager.h"

#include "engine_lock/WriteLockHandle.h"
#include "engine_lock/StackDbLockUnlocker.h"

#include "base/StackRelease.h"

namespace codablecash {

AlterDropIndexCommandLog::AlterDropIndexCommandLog() : AbstractAlterCommandLog(AbstractTransactionLog::TRX_ALTER_DROP_INDEX) {
	this->command = nullptr;
}

AlterDropIndexCommandLog::~AlterDropIndexCommandLog() {
	delete this->command;
}

void AlterDropIndexCommandLog::setCommand(AlterDropIndexCommand* command) noexcept {
	this->command = command;
}

int AlterDropIndexCommandLog::binarySize() const {
	CodeElement::checkNotNull(this->command);

	int total = sizeof(uint8_t);

	total += AbstractAlterCommandLog::binarySize();
	total += this->command->binarySize();

	return total;
}

void AlterDropIndexCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_DROP_INDEX);

	AbstractAlterCommandLog::toBinary(out);
	this->command->toBinary(out);
}

void AlterDropIndexCommandLog::fromBinary(ByteBuffer* in) {
	AbstractAlterCommandLog::fromBinary(in);

	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_DROP_INDEX);

	this->command = dynamic_cast<AlterDropIndexCommand*>(element);
}

void AlterDropIndexCommandLog::commit(CdbTransactionManager* trxManager) {
	WriteLockHandle* lockH = trxManager->databaseWriteLock();
	StackDbLockUnlocker unlocker(lockH);

	trxManager->commitAlterTable(this);
}

void AlterDropIndexCommandLog::initCommandParam(VirtualMachine* vm, TableIdentifier* tableId) {
	this->command->interpret(vm, this, tableId);
}

} /* namespace codablecash */
