/*
 * TableIdentifier.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/TableIdentifier.h"
#include "base/UnicodeString.h"

namespace alinous {

TableIdentifier::TableIdentifier() : AbstractSQLExpression(CodeElement::SQL_EXP_TABLE_ID) {
	this->schema = nullptr;
	this->tableName =nullptr;
}

TableIdentifier::~TableIdentifier() {
	delete this->schema;
	delete this->tableName;
}

void TableIdentifier::setSchema(UnicodeString* schema) noexcept {
	this->schema = schema;
}

void TableIdentifier::setTableName(UnicodeString* tableName) noexcept {
	this->tableName = tableName;
}

} /* namespace alinous */
