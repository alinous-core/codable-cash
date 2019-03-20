/*
 * SQLLikeExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLLikeExpression.h"
#include "sql_expression/SQLLiteral.h"

namespace alinous {

SQLLikeExpression::SQLLikeExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_LIKE) {
	this->left = nullptr;
	this->right = nullptr;
	this->escape = nullptr;
}

SQLLikeExpression::~SQLLikeExpression() {
	delete this->left;
	delete this->right;
	delete this->escape;
}

void SQLLikeExpression::setLeft(AbstractSQLExpression* left) noexcept {
	this->left = left;
}

void SQLLikeExpression::setRight(SQLLiteral* right) noexcept {
	this->right = right;
}

void SQLLikeExpression::setEscape(SQLLiteral* escape) noexcept {
	this->escape = escape;
}

int SQLLikeExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->right);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->right->binarySize();

	total += sizeof(uint8_t);
	if(this->escape != nullptr){
		total += this->escape->binarySize();
	}

	return total;
}

void SQLLikeExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->right);

	out->putShort(CodeElement::SQL_EXP_LIKE);
	this->left->toBinary(out);
	this->right->toBinary(out);

	out->put(this->escape != nullptr ? 1 : 0);
	if(this->escape != nullptr){
		this->escape->toBinary(out);
	}
}

void SQLLikeExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->left = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_LITERAL);
	this->right = dynamic_cast<SQLLiteral*>(element);

	uint8_t bl = in->get();
	if(bl == 1){
		element = createFromBinary(in);
		checkKind(element, CodeElement::SQL_EXP_LITERAL);
		this->escape = dynamic_cast<SQLLiteral*>(element);
	}
}

} /* namespace alinous */
