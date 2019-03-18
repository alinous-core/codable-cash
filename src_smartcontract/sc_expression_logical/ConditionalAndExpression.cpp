/*
 * ConditionalAndExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_logical/ConditionalAndExpression.h"

namespace alinous {

ConditionalAndExpression::ConditionalAndExpression() : AbstractBinaryExpression(CodeElement::EXP_CND_AND) {
}

ConditionalAndExpression::~ConditionalAndExpression() {
}

int ConditionalAndExpression::binarySize() const {
}

void ConditionalAndExpression::toBinary(ByteBuffer* out) {
}

void ConditionalAndExpression::fromBinary(ByteBuffer* in) {
}


} /* namespace alinous */
