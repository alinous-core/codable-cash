/*
 * SQLNotExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLNotExpression.h"

namespace alinous {

SQLNotExpression::SQLNotExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_NOT) {
	this->exp = nullptr;
}

SQLNotExpression::~SQLNotExpression() {
	delete this->exp;
}

void SQLNotExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLNotExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void SQLNotExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_EXP_NOT);
	this->exp->toBinary(out);
}

void SQLNotExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);
}

} /* namespace alinous */
