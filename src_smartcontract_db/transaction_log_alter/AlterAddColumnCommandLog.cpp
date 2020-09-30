/*
 * AlterAddColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterAddColumnCommandLog.h"

#include "sql_ddl_alter/AlterAddColumnCommand.h"

#include "sc/CodeElement.h"

#include "transaction/CdbTransactionManager.h"

#include "engine_lock/WriteLockHandle.h"

#include "base/StackRelease.h"

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

	total += AbstractAlterCommandLog::binarySize();
	total += this->command->binarySize();

	return total;
}

void AlterAddColumnCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_ADD_COLUMN);

	AbstractAlterCommandLog::toBinary(out);
	this->command->toBinary(out);
}

void AlterAddColumnCommandLog::fromBinary(ByteBuffer* in) {
	AbstractAlterCommandLog::fromBinary(in);

	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_ADD_COLUMN);

	this->command = dynamic_cast<AlterAddColumnCommand*>(element);
}

void AlterAddColumnCommandLog::commit(CdbTransactionManager* trxManager) {
	WriteLockHandle* lockH = trxManager->databaseWriteLock(); __STP(lockH);  // TODO: lock

	trxManager->commitAlterTable(this);
}

void AlterAddColumnCommandLog::initCommandParam(VirtualMachine* vm) {
}

} /* namespace codablecash */
