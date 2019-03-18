/*
 * UpdateStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml/UpdateStatement.h"
#include "sql_dml_parts/SQLWhere.h"
#include "sql_dml_parts/SQLSet.h"

#include "sql_join_parts/TableIdentifier.h"

namespace alinous {

UpdateStatement::UpdateStatement() : AbstractSQLStatement(CodeElement::DML_STMT_UPDATE) {
	this->tableId = nullptr;
	this->set = nullptr;
	this->where = nullptr;
}

UpdateStatement::~UpdateStatement() {
	delete this->tableId;
	delete this->set;
	delete this->where;
}

void UpdateStatement::setTable(TableIdentifier* tableId) noexcept {
	this->tableId = tableId;
}

void UpdateStatement::setSet(SQLSet* set) noexcept {
	this->set = set;
}

void UpdateStatement::setWhere(SQLWhere* where) noexcept {
	this->where = where;
}

int UpdateStatement::binarySize() const {
}

void UpdateStatement::toBinary(ByteBuffer* out) {
}

void UpdateStatement::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
