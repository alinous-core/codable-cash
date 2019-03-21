/*
 * NegateExpression.cpp
 *
 *  Created on: 2019/02/14
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/NegateExpression.h"

namespace alinous {

NegateExpression::NegateExpression() : AbstractExpression(CodeElement::EXP_NEGATE) {
	this->exp = nullptr;
}

NegateExpression::~NegateExpression() {
	delete this->exp;
}

void NegateExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}


int NegateExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void NegateExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_NEGATE);
	this->exp->toBinary(out);
}

void NegateExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

} /* namespace alinous */
