/*
 * ForStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement_ctrl/ForStatement.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

ForStatement::ForStatement() : AbstractStatement(CodeElement::STMT_FOR) {
	this->stmt = nullptr;
	this->init = nullptr;
	this->cond = nullptr;
	this->postLoop = nullptr;
}

ForStatement::~ForStatement() {
	delete this->stmt;
	delete this->init;
	delete this->cond;
	delete this->postLoop;
}

void ForStatement::setStatement(AbstractStatement* stmt) noexcept {
	this->stmt = stmt;
}

void ForStatement::setInit(AbstractStatement* init) noexcept {
	this->init = init;
}

void ForStatement::setCondition(AbstractExpression* cond) noexcept {
	this->cond = cond;
}

void ForStatement::setPostLoop(AbstractExpression* postLoop) noexcept {
	this->postLoop = postLoop;
}

} /* namespace alinous */

int alinous::ForStatement::binarySize() const {
}

void alinous::ForStatement::toBinary(ByteBuffer* out) {
}

void alinous::ForStatement::fromBinary(ByteBuffer* in) {
}
