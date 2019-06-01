/*
 * RelationalExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "sc_expression_logical/RelationalExpression.h"

namespace alinous {

RelationalExpression::RelationalExpression() : AbstractExpression(CodeElement::EXP_CND_RELATIONAL) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

RelationalExpression::~RelationalExpression() {
	delete this->left;
	delete this->right;
}

void RelationalExpression::preAnalyze(AnalyzeContext* actx) {
	this->left->setParent(this);
	this->left->preAnalyze(actx);

	this->right->setParent(this);
	this->right->preAnalyze(actx);
}

void RelationalExpression::analyze(AnalyzeContext* actx) {
	this->left->analyze(actx);
	this->right->analyze(actx);
}

void RelationalExpression::setLeft(AbstractExpression* exp) noexcept {
	this->left = exp;
}

void RelationalExpression::setRight(AbstractExpression* exp) noexcept {
	this->right = exp;
}

void RelationalExpression::setOp(uint8_t op) noexcept {
	this->op = op;
}

int RelationalExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->right);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->right->binarySize();
	total += sizeof(uint8_t);

	return total;
}

void RelationalExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->right);

	out->putShort(CodeElement::EXP_CND_RELATIONAL);
	this->left->toBinary(out);
	this->right->toBinary(out);
	out->put(this->op);
}

void RelationalExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->left = dynamic_cast<AbstractExpression*>(element);

	element = createFromBinary(in);
	checkIsExp(element);
	this->right = dynamic_cast<AbstractExpression*>(element);

	this->op = in->get();
}

} /* namespace alinous */
