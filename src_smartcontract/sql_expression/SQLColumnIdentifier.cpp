/*
 * SQLColumnIdentifier.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLColumnIdentifier.h"
#include "base/UnicodeString.h"

namespace alinous {

SQLColumnIdentifier::SQLColumnIdentifier() : AbstractSQLExpression(CodeElement::SQL_EXP_COLUMN_ID){
	this->schema = nullptr;
	this->tableName =nullptr;
	this->columnName =nullptr;
}

SQLColumnIdentifier::~SQLColumnIdentifier() {
	delete this->schema;
	delete this->tableName;
	delete this->columnName;
}

void SQLColumnIdentifier::setSchema(UnicodeString* schema) noexcept {
	this->schema = schema;
}

void SQLColumnIdentifier::setTableName(UnicodeString* tableName) noexcept {
	this->tableName = tableName;
}

void SQLColumnIdentifier::setColumnName(UnicodeString* columnName) noexcept {
	this->columnName = columnName;
}

} /* namespace alinous */
