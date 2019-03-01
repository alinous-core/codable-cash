/*
 * SQLJoinPart.cpp
 *
 *  Created on: 2019/02/25
 *      Author: iizuka
 */

#include "sql_join_parts/SQLJoinPart.h"

namespace alinous {

SQLJoinPart::SQLJoinPart() : AbstractJoinPart(CodeElement::SQL_EXP_JOIN_PART) {
	this->joinType = 0;

}

SQLJoinPart::~SQLJoinPart() {

}

void SQLJoinPart::setJoinType(uint8_t joinType) noexcept {
	this->joinType = joinType;
}

} /* namespace alinous */
