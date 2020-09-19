/*
 * AlterDropIndexCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterDropIndexCommandLog.h"

#include "sql_ddl_alter/AlterDropIndexCommand.h"

#include "transaction/CdbTransactionManager.h"

#include "engine_lock/WriteLockHandle.h"

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
	total += this->command->binarySize();

	return total;
}

void AlterDropIndexCommandLog::toBinary(ByteBuffer* out) const {
	CodeElement::checkNotNull(this->command);

	out->put(AbstractTransactionLog::TRX_ALTER_DROP_INDEX);
	this->command->toBinary(out);
}

void AlterDropIndexCommandLog::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::DDL_ALTER_DROP_INDEX);

	this->command = dynamic_cast<AlterDropIndexCommand*>(element);
}

void AlterDropIndexCommandLog::commit(CdbTransactionManager* trxManager) {
	WriteLockHandle* lockH = trxManager->databaseWriteLock(); __STP(lockH);

	trxManager->commitAlterTable(this);
}

void AlterDropIndexCommandLog::preAnalyze(AnalyzeContext* actx) {
}

void AlterDropIndexCommandLog::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterDropIndexCommandLog::analyze(AnalyzeContext* actx) {
}

void AlterDropIndexCommandLog::interpret(VirtualMachine* vm) {
}

} /* namespace codablecash */
