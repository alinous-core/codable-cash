/*
 * RelationalExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "lang/sc_expression_logical/RelationalExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_ref/PrimitiveReference.h"

namespace alinous {

RelationalExpression::RelationalExpression() : AbstractExpression(CodeElement::EXP_CND_RELATIONAL) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = GT;
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

	AnalyzedType atL = this->left->getType(actx);
	AnalyzedType atR = this->right->getType(actx);

	if(!atL.isPrimitiveInteger() || !atR.isPrimitiveInteger()){
		actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_PRIMITIVE, this, L"Relational expression requires integer parameters.", {});
	}

}

void RelationalExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->left->analyzeTypeRef(actx);
	this->right->analyzeTypeRef(actx);
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

AnalyzedType RelationalExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void RelationalExpression::init(VirtualMachine* vm) {
	this->left->init(vm);
	this->right->init(vm);
}

AbstractVmInstance* RelationalExpression::interpret(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* leftV = releaser.registerInstance(this->left->interpret(vm));
	AbstractVmInstance* rightV = releaser.registerInstance(this->right->interpret(vm));

	PrimitiveReference* p1 = dynamic_cast<PrimitiveReference*>(leftV);
	PrimitiveReference* p2 = dynamic_cast<PrimitiveReference*>(rightV);

	int result = p1->valueCompare(p2);

	PrimitiveReference* bl = nullptr;

	switch(this->op){
	case RelationalExpression::GT_EQ:
		bl = makeBoolInst(vm, result >= 0);
		break;
	case RelationalExpression::LT:
		bl = makeBoolInst(vm, result < 0);
		break;
	case RelationalExpression::LT_EQ:
		bl = makeBoolInst(vm, result <= 0);
		break;
	case RelationalExpression::GT:
	default:
		bl = makeBoolInst(vm, result > 0);
		break;
	}

	return bl;
}

PrimitiveReference* RelationalExpression::makeBoolInst(VirtualMachine* vm, bool value) const noexcept {
	return PrimitiveReference::createBoolReference(vm, value ? 1 : 0);
}

} /* namespace alinous */
