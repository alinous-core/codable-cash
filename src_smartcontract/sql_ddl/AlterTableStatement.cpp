/*
 * AlterTableStatement.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl/AlterTableStatement.h"

#include "sql_join_parts/TableIdentifier.h"

#include "sql_ddl_alter/AlterAddColumnCommand.h"

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
}

void AlterTableStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterTableStatement::analyze(AnalyzeContext* actx) {
}

int AlterTableStatement::binarySize() const {
}

void AlterTableStatement::toBinary(ByteBuffer* out) {
}

void AlterTableStatement::fromBinary(ByteBuffer* in) {
}

void AlterTableStatement::interpret(VirtualMachine* vm) {
}

} /* namespace alinous */
