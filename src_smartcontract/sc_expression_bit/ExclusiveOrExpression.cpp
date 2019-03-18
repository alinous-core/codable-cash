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
}

void ExclusiveOrExpression::toBinary(ByteBuffer* out) {
}

void ExclusiveOrExpression::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
