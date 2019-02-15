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

} /* namespace alinous */
