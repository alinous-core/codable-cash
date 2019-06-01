/*
 * ParenthesisExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/ParenthesisExpression.h"

namespace alinous {

ParenthesisExpression::ParenthesisExpression() : AbstractExpression(CodeElement::EXP_PARENTHESIS) {
	this->exp = nullptr;
}

ParenthesisExpression::~ParenthesisExpression() {
	delete this->exp;
}

void ParenthesisExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void ParenthesisExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
}

void ParenthesisExpression::setExp(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int ParenthesisExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void ParenthesisExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_PARENTHESIS);
	this->exp->toBinary(out);
}

void ParenthesisExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}
} /* namespace alinous */
