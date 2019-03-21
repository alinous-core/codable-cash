/*
 * SQLEqualityExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLEqualityExpression.h"

namespace alinous {

SQLEqualityExpression::SQLEqualityExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_EQUALITY) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

SQLEqualityExpression::~SQLEqualityExpression() {
	delete this->left;
	delete this->right;
}

void SQLEqualityExpression::setLeft(AbstractSQLExpression* exp) noexcept {
	this->left = exp;
}

void SQLEqualityExpression::setRight(AbstractSQLExpression* exp) noexcept {
	this->right = exp;
}

void SQLEqualityExpression::setOp(uint8_t op) noexcept {
	this->op = op;
}

int SQLEqualityExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->right);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->right->binarySize();
	total += sizeof(uint8_t);

	return total;
}

void SQLEqualityExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->right);

	out->putShort(CodeElement::SQL_EXP_EQUALITY);
	this->left->toBinary(out);
	this->right->toBinary(out);
	out->put(this->op);
}

void SQLEqualityExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->left = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkIsSQLExp(element);
	this->right = dynamic_cast<AbstractSQLExpression*>(element);

	this->op = in->get();
}

} /* namespace alinous */
