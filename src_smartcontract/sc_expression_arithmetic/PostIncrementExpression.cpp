/*
 * PostIncrementExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/PostIncrementExpression.h"

namespace alinous {

PostIncrementExpression::PostIncrementExpression() : AbstractExpression(CodeElement::EXP_POST_INC) {
	this->exp = nullptr;
	this->ope = 0;
}

PostIncrementExpression::~PostIncrementExpression() {
	delete this->exp;
}

void PostIncrementExpression::preAnalyze(AnalyzeContext* actx) {
	// FIXME
}

void PostIncrementExpression::analyze(AnalyzeContext* actx) {
	// FIXME
}

void PostIncrementExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void PostIncrementExpression::setOpe(int ope) noexcept {
	this->ope = ope;
}

int PostIncrementExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void PostIncrementExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_POST_INC);
	this->exp->toBinary(out);
}

void PostIncrementExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

} /* namespace alinous */
