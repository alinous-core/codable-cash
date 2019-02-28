/*
 * SQLJoin.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */
#include "sql_join_parts/SQLJoin.h"
#include "sql_join_parts/SQLJoinPart.h"

namespace alinous {

SQLJoin::SQLJoin() : AbstractJoinPart(CodeElement::SQL_EXP_JOIN) {
}

SQLJoin::~SQLJoin() {
	this->list.deleteElements();
}

void SQLJoin::addJoinPart(SQLJoinPart* part) noexcept {
	this->list.addElement(part);
}

} /* namespace alinous */
