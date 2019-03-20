/*
 * SQLIsNullExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLIsNullExpression.h"

namespace alinous {

SQLIsNullExpression::SQLIsNullExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_IS_NULL) {
	this->exp = nullptr;
	this->notnull = false;
}

SQLIsNullExpression::~SQLIsNullExpression() {
	delete this->exp;
}

void SQLIsNullExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

void SQLIsNullExpression::setNotNull(bool notnull) noexcept {
	this->notnull = notnull;
}

int SQLIsNullExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();
	total += sizeof(uint8_t);

	return total;
}

void SQLIsNullExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_EXP_IS_NULL);
	this->exp->toBinary(out);
	out->put(this->notnull ? 1 : 0);
}

void SQLIsNullExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);

	int8_t bl = in->get();
	this->notnull = (bl == 1);
}


} /* namespace alinous */
