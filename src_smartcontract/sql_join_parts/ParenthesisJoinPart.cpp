/*
 * ParenthesisJoinPart.cpp
 *
 *  Created on: 2019/02/28
 *      Author: iizuka
 */

#include "sql_join_parts/ParenthesisJoinPart.h"

namespace alinous {

ParenthesisJoinPart::ParenthesisJoinPart() : AbstractJoinPart(CodeElement::SQL_EXP_PARENTHESIS_JOIN_PART) {
	this->part = nullptr;
}

ParenthesisJoinPart::~ParenthesisJoinPart() {
	delete this->part;
}

void ParenthesisJoinPart::setPart(AbstractJoinPart* part) noexcept {
	this->part = part;
}

} /* namespace alinous */
