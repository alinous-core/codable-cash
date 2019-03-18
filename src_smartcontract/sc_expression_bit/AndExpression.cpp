/*
 * AndExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/AndExpression.h"

namespace alinous {

AndExpression::AndExpression() : AbstractBinaryExpression(CodeElement::EXP_AND) {
}

AndExpression::~AndExpression() {
}

} /* namespace alinous */

int alinous::AndExpression::binarySize() const {
}

void alinous::AndExpression::toBinary(ByteBuffer* out) {
}

void alinous::AndExpression::fromBinary(ByteBuffer* in) {
}
