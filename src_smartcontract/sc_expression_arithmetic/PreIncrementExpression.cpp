/*
 * PreIncrementExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/PreIncrementExpression.h"

namespace alinous {

PreIncrementExpression::PreIncrementExpression() : AbstractExpression(CodeElement::EXP_PRE_INC) {
	this->exp = nullptr;
	this->ope = 0;
}

PreIncrementExpression::~PreIncrementExpression() {
	delete this->exp;
}

void PreIncrementExpression::preAnalyze(AnalyzeContext* actx) {
	// FIXME
}

void PreIncrementExpression::analyze(AnalyzeContext* actx) {
	// FIXME
}

void PreIncrementExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void PreIncrementExpression::setOpe(int ope) noexcept {
	this->ope = ope;
}

int PreIncrementExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void PreIncrementExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_PRE_INC);
	this->exp->toBinary(out);
}

void PreIncrementExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

} /* namespace alinous */
