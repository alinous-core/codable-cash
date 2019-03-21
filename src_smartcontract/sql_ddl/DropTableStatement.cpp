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

void DropTableStatement::setTableId(TableIdentifier* tableId) noexcept {
	this->tableId = tableId;
}

int DropTableStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void DropTableStatement::toBinary(ByteBuffer* out) {
}

void DropTableStatement::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
