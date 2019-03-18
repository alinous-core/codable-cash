/*
 * ExpressionStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement/ExpressionStatement.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

ExpressionStatement::ExpressionStatement() : AbstractStatement(CodeElement::STMT_EXPRESSION) {
	this->exp = nullptr;
}

ExpressionStatement::~ExpressionStatement() {
	delete this->exp;
}

void ExpressionStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */

int alinous::ExpressionStatement::binarySize() const {
}

void alinous::ExpressionStatement::toBinary(ByteBuffer* out) {
}

void alinous::ExpressionStatement::fromBinary(ByteBuffer* in) {
}
