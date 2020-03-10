/*
 * EqualityExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_logical/EqualityExpression.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance/AbstractVmInstance.h"

#include "instance_ref/PrimitiveReference.h"


namespace alinous {

EqualityExpression::EqualityExpression() : AbstractExpression(CodeElement::EXP_CND_EQ) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = EQ;
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

AnalyzedType EqualityExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void EqualityExpression::init(VirtualMachine* vm) {
	this->left->init(vm);
	this->right->init(vm);
}

AbstractVmInstance* EqualityExpression::interpret(VirtualMachine* vm) {
	AbstractVmInstance* leftv = this->left->interpret(vm);
	AbstractVmInstance* rightv = this->left->interpret(vm);

	int result = leftv->valueCompare(rightv);
	bool bl = (result == 0);
	if(this->op == NOT_EQ){
		bl = !bl;
	}

	PrimitiveReference* ret = PrimitiveReference::createBoolReference(vm, bl ? 1 : 0);

	return ret; // FIXME expression::interpret()
}

} /* namespace alinous */
