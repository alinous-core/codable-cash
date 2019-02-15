/*
 * WhileStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement_ctrl/WhileStatement.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

WhileStatement::WhileStatement() : AbstractStatement(CodeElement::STMT_WHILE) {
	this->exp = nullptr;
	this->stmt = nullptr;
}

WhileStatement::~WhileStatement() {
	delete this->exp;
	delete this->stmt;
}

void WhileStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void WhileStatement::setStatement(AbstractStatement* stmt) noexcept {
	this->stmt = stmt;
}

} /* namespace alinous */
