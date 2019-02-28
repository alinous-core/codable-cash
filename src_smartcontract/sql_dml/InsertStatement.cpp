/*
 * InsertStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml/InsertStatement.h"

#include "sql_dml_parts/SQLColumnsList.h"
#include "sql_expression/SQLExpressionList.h"
#include "sql_join_parts/TableIdentifier.h"

namespace alinous {

InsertStatement::InsertStatement() : AbstractSQLStatement(CodeElement::DML_STMT_INSERT) {
	this->tableId = nullptr;
	this->columns = nullptr;
	this->expList = nullptr;
}

InsertStatement::~InsertStatement() {
	delete this->tableId;
	delete this->columns;
	delete this->expList;
}

void InsertStatement::setTable(TableIdentifier* tableId) noexcept {
	this->tableId = tableId;
}

void InsertStatement::setColumns(SQLColumnsList* columns) noexcept {
	this->columns = columns;
}

void InsertStatement::setExpressionList(SQLExpressionList* expList) noexcept {
	this->expList = expList;
}


} /* namespace alinous */
