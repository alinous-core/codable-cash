/*
 * IfStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement_ctrl/IfStatement.h"
#include "sc_expression/AbstractExpression.h"
namespace alinous {

IfStatement::IfStatement() : AbstractStatement(CodeElement::STMT_IF) {
	this->exp = nullptr;
	this->stmt = nullptr;
}

IfStatement::~IfStatement() {
	delete this->exp;
	delete this->stmt;
}

void IfStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void IfStatement::setStatement(AbstractStatement* stmt) noexcept {
	this->stmt = stmt;
}

} /* namespace alinous */

int alinous::IfStatement::binarySize() const {
}

void alinous::IfStatement::toBinary(ByteBuffer* out) {
}

void alinous::IfStatement::fromBinary(ByteBuffer* in) {
}
