/*
 * SQLInExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLInExpression.h"
#include "sql_expression/SQLExpressionList.h"

namespace alinous {

SQLInExpression::SQLInExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_IN) {
	this->left = nullptr;
	this->list = nullptr;
}

SQLInExpression::~SQLInExpression() {
	delete this->left;
	delete this->list;
}

void SQLInExpression::setLeft(AbstractSQLExpression* left) noexcept {
	this->left = left;
}

void SQLInExpression::setList(SQLExpressionList* list) noexcept {
	this->list = list;
}

int SQLInExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->list);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->list->binarySize();

	return total;
}

void SQLInExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->list);

	out->putShort(CodeElement::SQL_EXP_IN);
	this->left->toBinary(out);
	this->list->toBinary(out);
}

void SQLInExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->left = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_EXP_LIST);
	this->list = dynamic_cast<SQLExpressionList*>(element);
}

} /* namespace alinous */
