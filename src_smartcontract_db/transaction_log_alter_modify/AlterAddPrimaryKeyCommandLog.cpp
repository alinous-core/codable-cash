/*
 * AlterAddPrimaryKeyCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"

#include "sql_ddl_alter_modify/AlterAddPrimaryKeyCommand.h"

#include "transaction/CdbTransactionManager.h"

#include "engine_lock/WriteLockHandle.h"

#include "base/StackRelease.h"

namespace codablecash {

AlterAddPrimaryKeyCommandLog::AlterAddPrimaryKeyCommandLog() : AbstractAlterCommandLog(AbstractTransactionLog::TRX_ALTER_ADD_PRIMARY_KEY){
	this->command = nullptr;
}

AlterAddPrimaryKeyCommandLog::~AlterAddPrimaryKeyCommandLog() {
	delete this->command;
}

void AlterAddPrimaryKeyCommandLog::setCommand(AlterAddPrimaryKeyCommand* command) noexcept {
	this->command = command;
}

int AlterAddPrimaryKeyCommandLog::binarySize() const {
	CodeElement::checkNotNull(this->command);

	int total = sizeof(uint8_t);

	total += AbstractAlterCommandLog::binarySize();
	total += this->command->binarySize();

	return total;
}

void AlterAddPrimaryKeyCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_ADD_PRIMARY_KEY);

	AbstractAlterCommandLog::toBinary(out);
	this->command->toBinary(out);
}

void AlterAddPrimaryKeyCommandLog::fromBinary(ByteBuffer* in) {
	AbstractAlterCommandLog::fromBinary(in);

	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_ADD_PRIMARY_KEY);

	this->command = dynamic_cast<AlterAddPrimaryKeyCommand*>(element);
}

void AlterAddPrimaryKeyCommandLog::commit(CdbTransactionManager* trxManager) {
	WriteLockHandle* lockH = trxManager->databaseWriteLock(); __STP(lockH);

	trxManager->commitAlterTable(this);
}

void AlterAddPrimaryKeyCommandLog::initCommandParam(VirtualMachine* vm) {
}

} /* namespace codablecash */
