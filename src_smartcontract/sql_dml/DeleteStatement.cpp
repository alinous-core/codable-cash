/*
 * DeleteStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml/DeleteStatement.h"

#include "sql_dml_parts/SQLFrom.h"
#include "sql_dml_parts/SQLWhere.h"

namespace alinous {

DeleteStatement::DeleteStatement() : AbstractSQLStatement(CodeElement::DML_STMT_DELETE) {
	this->from = nullptr;
	this->where = nullptr;
}

DeleteStatement::~DeleteStatement() {
	delete this->from;
	delete this->where;
}

void DeleteStatement::setFrom(SQLFrom* from) noexcept {
	this->from = from;
}

void DeleteStatement::setWhere(SQLWhere* where) noexcept {
	this->where = where;
}


} /* namespace alinous */
