/*
 * AbstractExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/AbstractExpression.h"

namespace alinous {

AbstractExpression::AbstractExpression(int kind) : CodeElement(kind) {
}

AbstractExpression::~AbstractExpression() {
}

} /* namespace alinous */
