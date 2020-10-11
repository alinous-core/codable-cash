/*
 * AlterModifyCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterModifyCommandLog.h"

#include "sql_ddl_alter_modify/AlterModifyCommand.h"

#include "engine_lock/WriteLockHandle.h"
#include "engine_lock/StackDbLockUnlocker.h"

#include "base/StackRelease.h"

#include "transaction/CdbTransactionManager.h"

#include "base/UnicodeString.h"


namespace codablecash {

AlterModifyCommandLog::AlterModifyCommandLog() : AbstractAlterCommandLog(AbstractTransactionLog::TRX_ALTER_MODIFY) {
	this->command = nullptr;
	this->length = 0;
}

AlterModifyCommandLog::~AlterModifyCommandLog() {
	delete this->command;
}

void AlterModifyCommandLog::setCommand(AlterModifyCommand* command) noexcept {
	this->command = command;
}

int AlterModifyCommandLog::binarySize() const {
	CodeElement::checkNotNull(this->command);

	int total = sizeof(uint8_t);

	total += AbstractAlterCommandLog::binarySize();
	total += this->command->binarySize();

	total += sizeof(int64_t); // length

	return total;
}

void AlterModifyCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_MODIFY);

	AbstractAlterCommandLog::toBinary(out);
	this->command->toBinary(out);

	out->putLong(this->length);
}

void AlterModifyCommandLog::fromBinary(ByteBuffer* in) {
	AbstractAlterCommandLog::fromBinary(in);

	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_MODIFY);

	this->command = dynamic_cast<AlterModifyCommand*>(element);

	this->length = in->getLong();
}

void AlterModifyCommandLog::commit(CdbTransactionManager* trxManager) {
	WriteLockHandle* lockH = trxManager->databaseWriteLock();
	StackDbLockUnlocker unlocker(lockH);

	trxManager->commitAlterTable(this);
}

void AlterModifyCommandLog::initCommandParam(VirtualMachine* vm, TableIdentifier* tableId) {
	this->command->interpret(vm, this, tableId);
}

void AlterModifyCommandLog::setLength(int64_t length) noexcept {
	this->length = length;
}

void AlterModifyCommandLog::reanalyze(AnalyzeContext* ctx, CodeElement* parent) {
	this->command->setParent(parent);
	this->command->preAnalyze(ctx);

	this->command->analyzeTypeRef(ctx);

	this->command->analyze(ctx);
}


} /* namespace codablecash */
