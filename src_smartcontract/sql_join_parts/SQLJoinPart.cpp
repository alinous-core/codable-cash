/*
 * SQLJoinPart.cpp
 *
 *  Created on: 2019/02/25
 *      Author: iizuka
 */

#include "sql_join_parts/SQLJoinPart.h"
#include "sql_join_parts/TableIdentifier.h"

namespace alinous {

SQLJoinPart::SQLJoinPart() : AbstractJoinPart(CodeElement::SQL_EXP_JOIN_PART) {
	this->joinType = 0;
	this->table = nullptr;
	this->exp = nullptr;
}

SQLJoinPart::~SQLJoinPart() {
	delete this->table;
	delete this->exp;
}

void SQLJoinPart::setJoinType(uint8_t joinType) noexcept {
	this->joinType = joinType;
}

void SQLJoinPart::setTable(TableIdentifier* table) noexcept {
	this->table = table;
}

void SQLJoinPart::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */


