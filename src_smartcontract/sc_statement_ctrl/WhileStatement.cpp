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

int WhileStatement::binarySize() const {
	checkNotNull(this->exp);
	checkNotNull(this->stmt);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();
	total += this->stmt->binarySize();

	return total;
}

void WhileStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);
	checkNotNull(this->stmt);

	out->putShort(CodeElement::STMT_WHILE);
	this->exp->toBinary(out);
	this->stmt->toBinary(out);
}

void WhileStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);

	element = createFromBinary(in);
	checkIsStatement(element);
	this->stmt = dynamic_cast<AbstractStatement*>(element);
}

} /* namespace alinous */
