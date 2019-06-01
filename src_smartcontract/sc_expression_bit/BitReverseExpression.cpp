/*
 * BitReverseExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/BitReverseExpression.h"

namespace alinous {

BitReverseExpression::BitReverseExpression() : AbstractExpression(CodeElement::EXP_BIT_REV) {
	this->exp = nullptr;
}

BitReverseExpression::~BitReverseExpression() {
	delete this->exp;
}


void BitReverseExpression::preAnalyze(AnalyzeContext* actx) {
	// FIXME
}

void BitReverseExpression::analyze(AnalyzeContext* actx) {
	// FIXME
}

void BitReverseExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int BitReverseExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void BitReverseExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_BIT_REV);
	this->exp->toBinary(out);
}

void BitReverseExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

} /* namespace alinous */
