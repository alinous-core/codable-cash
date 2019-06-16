/*
 * EqualityExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_logical/EqualityExpression.h"

#include "sc_analyze/AnalyzedType.h"

namespace alinous {

EqualityExpression::EqualityExpression() : AbstractExpression(CodeElement::EXP_CND_EQ) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

EqualityExpression::~EqualityExpression() {
	delete this->left;
	delete this->right;
}

void EqualityExpression::preAnalyze(AnalyzeContext* actx) {
	this->left->setParent(this);
	this->left->preAnalyze(actx);

	this->right->setParent(this);
	this->right->preAnalyze(actx);
}

void EqualityExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->left->analyzeTypeRef(actx);
	this->right->analyzeTypeRef(actx);
}

void EqualityExpression::analyze(AnalyzeContext* actx) {
	this->left->analyze(actx);
	this->right->analyze(actx);
}

void EqualityExpression::setLeft(AbstractExpression* exp) noexcept {
	this->left = exp;
}

void EqualityExpression::setRight(AbstractExpression* exp) noexcept {
	this->right = exp;
}

void EqualityExpression::setOp(uint8_t op) noexcept {
	this->op = op;
}

int EqualityExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->right);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->right->binarySize();
	total += sizeof(uint8_t);

	return total;
}

void EqualityExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->right);

	out->putShort(CodeElement::EXP_CND_EQ);
	this->left->toBinary(out);
	this->right->toBinary(out);
	out->put(this->op);
}

void EqualityExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->left = dynamic_cast<AbstractExpression*>(element);

	element = createFromBinary(in);
	checkIsExp(element);
	this->right = dynamic_cast<AbstractExpression*>(element);

	this->op = in->get();
}

AnalyzedType EqualityExpression::getType() {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

AbstractVmInstance* EqualityExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
