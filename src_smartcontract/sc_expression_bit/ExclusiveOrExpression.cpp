/*
 * ExclusiveOrExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/ExclusiveOrExpression.h"

namespace alinous {

ExclusiveOrExpression::ExclusiveOrExpression() : AbstractBinaryExpression(CodeElement::EXP_EX_OR) {
}

ExclusiveOrExpression::~ExclusiveOrExpression() {
}

int ExclusiveOrExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void ExclusiveOrExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_EX_OR);
	AbstractBinaryExpression::toBinary(out);
}

void ExclusiveOrExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

} /* namespace alinous */
