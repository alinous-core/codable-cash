/*
 * DropTableStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_ddl/DropTableStatement.h"
#include "sql_expression/TableIdentifier.h"

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

} /* namespace alinous */
