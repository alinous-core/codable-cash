/*
 * DropTableStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_ddl/DropTableStatement.h"
#include "sql_join_parts/TableIdentifier.h"
namespace alinous {

DropTableStatement::DropTableStatement() : AbstractSQLStatement(CodeElement::DDL_DROP_TABLE) {
	this->tableId = nullptr;
}

DropTableStatement::~DropTableStatement() {
	delete this->tableId;
}

void DropTableStatement::preAnalyze(AnalyzeContext* actx) {

}

void DropTableStatement::analyze(AnalyzeContext* actx) {

}

void DropTableStatement::setTableId(TableIdentifier* tableId) noexcept {
	this->tableId = tableId;
}

int DropTableStatement::binarySize() const {
	checkNotNull(this->tableId);

	int total = sizeof(uint16_t);
	total += this->tableId->binarySize();

	return total;
}

void DropTableStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->tableId);

	out->putShort(CodeElement::DDL_DROP_TABLE);
	this->tableId->toBinary(out);
}

void DropTableStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_TABLE_ID);
	this->tableId = dynamic_cast<TableIdentifier*>(element);
}

void DropTableStatement::interpret(VirtualMachine* vm) {
	// FIXME SQL statement
}

} /* namespace alinous */
