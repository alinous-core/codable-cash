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
	this->first = nullptr;
}

SQLJoin::~SQLJoin() {
	this->list.deleteElements();
	delete this->first;
}

void SQLJoin::setFirst(AbstractJoinPart* first) noexcept {
	this->first = first;
}

void SQLJoin::addJoinPart(SQLJoinPart* part) noexcept {
	this->list.addElement(part);
}

} /* namespace alinous */
