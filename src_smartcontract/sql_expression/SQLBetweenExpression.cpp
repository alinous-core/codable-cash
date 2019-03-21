/*
 * SQLBetweenExpression.cpp
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#include "sql_expression/SQLBetweenExpression.h"

namespace alinous {

SQLBetweenExpression::SQLBetweenExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_BETWEEN) {
	this->left = nullptr;
	this->start = nullptr;
	this->end = nullptr;
}

SQLBetweenExpression::~SQLBetweenExpression() {
	delete this->left;
	delete this->start;
	delete this->end;
}

void SQLBetweenExpression::setLeft(AbstractSQLExpression* exp) noexcept {
	this->left = exp;
}

void SQLBetweenExpression::setStart(AbstractSQLExpression* exp) noexcept {
	this->start = exp;
}

void SQLBetweenExpression::setEnd(AbstractSQLExpression* exp) noexcept {
	this->end = exp;
}

int SQLBetweenExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->start);
	checkNotNull(this->end);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->start->binarySize();
	total += this->end->binarySize();

	return total;
}

void SQLBetweenExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->start);
	checkNotNull(this->end);

	out->putShort(CodeElement::SQL_EXP_BETWEEN);
	this->left->toBinary(out);
	this->start->toBinary(out);
	this->end->toBinary(out);
}

void SQLBetweenExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->left = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkIsSQLExp(element);
	this->start = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkIsSQLExp(element);
	this->end = dynamic_cast<AbstractSQLExpression*>(element);
}

} /* namespace alinous */
