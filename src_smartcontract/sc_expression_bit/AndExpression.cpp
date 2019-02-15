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
