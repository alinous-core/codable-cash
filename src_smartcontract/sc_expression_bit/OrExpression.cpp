/*
 * OrExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/OrExpression.h"

namespace alinous {

OrExpression::OrExpression() : AbstractBinaryExpression(CodeElement::EXP_OR) {
}

OrExpression::~OrExpression() {
}

int OrExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void OrExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_OR);
	AbstractBinaryExpression::toBinary(out);
}

void OrExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

} /* namespace alinous */
