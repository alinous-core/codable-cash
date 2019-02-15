/*
 * ReturnStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement_ctrl/ReturnStatement.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

ReturnStatement::ReturnStatement() : AbstractStatement(CodeElement::STMT_RETURN) {
	this->exp = nullptr;
}

ReturnStatement::~ReturnStatement() {
	delete this->exp;
}

void ReturnStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
