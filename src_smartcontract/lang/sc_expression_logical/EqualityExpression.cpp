/*
 * EqualityExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression_logical/EqualityExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/AbstractVmInstance.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "vm/type_check/AnalyzedTypeChecker.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"


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

	AnalyzedTypeChecker checker;
	checker.checkCompatibility(actx, this->left, this->right, true);
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
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* leftv = this->left->interpret(vm);
	releaser.registerInstance(leftv);
	AbstractVmInstance* rightv = this->right->interpret(vm);
	releaser.registerInstance(rightv);

	int result = leftv->valueCompare(rightv->getInstance());
	bool bl = (result == 0);
	if(this->op == NOT_EQ){
		bl = !bl;
	}

	PrimitiveReference* ret = PrimitiveReference::createBoolReference(vm, bl ? 1 : 0);

	return ret;
}

} /* namespace alinous */
