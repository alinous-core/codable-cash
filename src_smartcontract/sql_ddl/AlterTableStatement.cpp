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

	this->tableId = dynamic_cast<TableIdentifier*>(element);
	// FIXME error check

	element = createFromBinary(in);
	this->cmd =dynamic_cast<AbstractAlterDdlCommand*>(element);

}

void AlterTableStatement::interpret(VirtualMachine* vm) {
}

} /* namespace alinous */
