/*
 * AlterTableStatement.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "lang_sql/sql_ddl/AlterTableStatement.h"

#include "lang_sql/sql_join_parts/TableIdentifier.h"

#include "lang_sql/sql_ddl_alter/AlterAddColumnCommand.h"

#include "vm/vm_trx/VmTransactionHandler.h"

#include "vm/VirtualMachine.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "base/Exception.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "trx/transaction_log_alter/AbstractAlterCommandLog.h"

#include "lang_sql/sql_ddl_alter_modify/AlterModifyCommand.h"

#include "engine/sc/SmartContract.h"

namespace alinous {

AlterTableStatement::AlterTableStatement() : AbstractSQLStatement(CodeElement::DDL_ALTER_TABLE) {
	this->tableId = nullptr;
	this->cmd = nullptr;
}

AlterTableStatement::~AlterTableStatement() {
	delete this->tableId;
	delete this->cmd;
}

void AlterTableStatement::setTableId(TableIdentifier* tableId) noexcept {
	this->tableId = tableId;
}

void AlterTableStatement::setCommand(AbstractAlterDdlCommand* cmd) noexcept {
	this->cmd = cmd;
}

void AlterTableStatement::preAnalyze(AnalyzeContext* actx) {
	this->cmd->setParent(this);
	this->cmd->preAnalyze(actx);
}

void AlterTableStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->cmd->analyzeTypeRef(actx);
}

void AlterTableStatement::analyze(AnalyzeContext* actx) {
	this->cmd->analyze(actx);
}

int AlterTableStatement::binarySize() const {
	checkNotNull(this->tableId);
	checkNotNull(this->cmd);

	int total = sizeof(uint16_t);

	total += this->tableId->binarySize();
	total += this->cmd->binarySize();

	return total;
}

void AlterTableStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->tableId);
	checkNotNull(this->cmd);

	out->putShort(CodeElement::DDL_ALTER_TABLE);

	this->tableId->toBinary(out);
	this->cmd->toBinary(out);
}

void AlterTableStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_TABLE_ID);
	this->tableId = dynamic_cast<TableIdentifier*>(element);

	element = createFromBinary(in);
	checkIsAlterCommand(element);
	this->cmd =dynamic_cast<AbstractAlterDdlCommand*>(element);

}

void AlterTableStatement::interpret(VirtualMachine* vm) {
	AbstractAlterCommandLog* log = this->cmd->getCommandLog();

	TableIdentifier* table = new TableIdentifier(*this->tableId); __STP(table);
	if(table->getSchema() == nullptr){
		table->setSchema(new UnicodeString(vm->getCurrentSchema()));
	}
	log->setTableIdentifier(table);

	log->reanalyze(vm->getSmartContract()->getAnalyzeContext(), this);

	VmTransactionHandler* handler = vm->getTransactionHandler();
	try{
		log->initCommandParam(vm, table);

		handler->alterTable(log);
	}
	catch(Exception* e){
		DatabaseExceptionClassDeclare::throwException(e->getMessage(), vm, this);
		delete e;
		delete log;
	}
}

} /* namespace alinous */
