/*
 * ConditionalOrExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_logical/ConditionalOrExpression.h"

namespace alinous {

ConditionalOrExpression::ConditionalOrExpression() : AbstractBinaryExpression(CodeElement::EXP_CND_OR) {
}

ConditionalOrExpression::~ConditionalOrExpression() {
}

} /* namespace alinous */
