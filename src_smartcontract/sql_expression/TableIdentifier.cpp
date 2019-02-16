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
	this->scheme = nullptr;
	this->tableName =nullptr;
}

TableIdentifier::~TableIdentifier() {
	delete this->scheme;
	delete this->tableName;
}

void TableIdentifier::setScheme(UnicodeString* scheme) noexcept {
	this->scheme = scheme;
}

void TableIdentifier::setTableName(UnicodeString* tableName) noexcept {
	this->tableName = tableName;
}

} /* namespace alinous */
