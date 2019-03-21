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

int ParenthesisJoinPart::binarySize() const {
	checkNotNull(this->part);

	int total = sizeof(uint16_t);
	total += this->part->binarySize();

	return total;
}

void ParenthesisJoinPart::toBinary(ByteBuffer* out) {
	checkNotNull(this->part);

	out->putShort(CodeElement::SQL_EXP_PARENTHESIS_JOIN_PART);
	this->part->toBinary(out);
}

void ParenthesisJoinPart::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsJoinPart(element);
	this->part = dynamic_cast<AbstractJoinPart*>(element);
}

} /* namespace alinous */
