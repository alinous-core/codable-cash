/*
 * SelectStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml/SelectStatement.h"
#include "sql_dml_parts/SQLFrom.h"
#include "sql_dml_parts/SQLWhere.h"
#include "sql_dml_parts/SQLGroupBy.h"
#include "sql_dml_parts/SQLOrderBy.h"
#include "sql_dml_parts/SQLLimitOffset.h"
#include "sql_dml_parts/SQLSelectTargetList.h"

namespace alinous {

SelectStatement::SelectStatement() : AbstractSQLStatement(CodeElement::DML_STMT_SELECT) {
	this->list = nullptr;
	this->from = nullptr;
	this->where = nullptr;
	this->groupBy = nullptr;
	this->orderBy = nullptr;
	this->limitOffset = nullptr;
}

SelectStatement::~SelectStatement() {
	delete this->list;
	delete this->from;
	delete this->where;
	delete this->groupBy;
	delete this->orderBy;
	delete this->limitOffset;
}

void SelectStatement::setList(SQLSelectTargetList* list) noexcept {
	this->list = list;
}

void SelectStatement::setFrom(SQLFrom* from) noexcept {
	this->from = from;
}

void SelectStatement::setWhere(SQLWhere* where) noexcept {
	this->where = where;
}

void SelectStatement::setGroupBy(SQLGroupBy* groupBy) noexcept {
	this->groupBy = groupBy;
}

void SelectStatement::setOrderBy(SQLOrderBy* orderBy) noexcept {
	this->orderBy = orderBy;
}

void SelectStatement::setLimitOffset(SQLLimitOffset* limitOffset) noexcept {
	this->limitOffset = limitOffset;
}

} /* namespace alinous */
