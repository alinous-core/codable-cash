/*
 * AlterAddIndexCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterAddIndexCommandLog.h"

#include "sql_ddl_alter/AlterAddIndexCommand.h"

#include "transaction/CdbTransactionManager.h"

#include "engine_lock/WriteLockHandle.h"
#include "engine_lock/StackDbLockUnlocker.h"

#include "base/StackRelease.h"

namespace codablecash {

AlterAddIndexCommandLog::AlterAddIndexCommandLog() : AbstractAlterCommandLog(AbstractTransactionLog::TRX_ALTER_ADD_INDEX) {
	this->command = nullptr;
}

AlterAddIndexCommandLog::~AlterAddIndexCommandLog() {
	delete this->command;
}

void AlterAddIndexCommandLog::setCommand(AlterAddIndexCommand* command) noexcept {
	this->command = command;
}

int AlterAddIndexCommandLog::binarySize() const {
	CodeElement::checkNotNull(this->command);

	int total = sizeof(uint8_t);

	total += AbstractAlterCommandLog::binarySize();
	total += this->command->binarySize();

	return total;
}

void AlterAddIndexCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_ADD_INDEX);

	AbstractAlterCommandLog::toBinary(out);
	this->command->toBinary(out);
}

void AlterAddIndexCommandLog::fromBinary(ByteBuffer* in) {
	AbstractAlterCommandLog::fromBinary(in);

	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_ADD_INDEX);

	this->command = dynamic_cast<AlterAddIndexCommand*>(element);
}

void AlterAddIndexCommandLog::commit(CdbTransactionManager* trxManager) {
	WriteLockHandle* lockH = trxManager->databaseWriteLock();
	StackDbLockUnlocker unlocker(lockH);

	trxManager->commitAlterTable(this);
}

void AlterAddIndexCommandLog::initCommandParam(VirtualMachine* vm) {
}

} /* namespace codablecash */
