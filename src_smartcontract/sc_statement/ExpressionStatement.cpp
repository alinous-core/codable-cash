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

int ExpressionStatement::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void ExpressionStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::STMT_EXPRESSION);
	this->exp->toBinary(out);
}

void ExpressionStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

} /* namespace alinous */
