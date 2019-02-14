/*
 * AbstractBinaryExpression.cpp
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#include "sc_expression/AbstractBinaryExpression.h"

namespace alinous {

AbstractBinaryExpression::AbstractBinaryExpression(int kind) : AbstractExpression(kind) {
}

AbstractBinaryExpression::~AbstractBinaryExpression() {
	this->list.deleteElements();
}

void AbstractBinaryExpression::addExp(AbstractExpression* exp) noexcept {
	this->list.addElement(exp);
}

} /* namespace alinous */
