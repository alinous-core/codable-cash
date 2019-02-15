/*
 * DoWhileStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement_ctrl/DoWhileStatement.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

DoWhileStatement::DoWhileStatement() : AbstractStatement(CodeElement::STMT_DO_WHILE) {
	this->exp = nullptr;
	this->stmt = nullptr;
}

DoWhileStatement::~DoWhileStatement() {
	delete this->exp;
	delete this->stmt;
}

void DoWhileStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void DoWhileStatement::setStatement(AbstractStatement* stmt) noexcept {
	this->stmt = stmt;
}

} /* namespace alinous */
