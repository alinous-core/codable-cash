/*
 * BitReverseExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression_bit/BitReverseExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/ValidationError.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_gc/GcManager.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"

namespace alinous {

BitReverseExpression::BitReverseExpression() : AbstractExpression(CodeElement::EXP_BIT_REV) {
	this->exp = nullptr;
	this->atype = nullptr;
}

BitReverseExpression::~BitReverseExpression() {
	delete this->exp;
	delete this->atype;
}


void BitReverseExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void BitReverseExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void BitReverseExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);

	AnalyzedType at = this->exp->getType(actx);
	this->atype = new AnalyzedType(at);

	AnalyzedType type = getType(actx);
	if(!type.isPrimitiveInteger()){
		actx->addValidationError(ValidationError::CODE_ARITHMETIC_NON_INTEGER, this, L"Can not use arithmetic operator to non integer value.", {});
	}
}

void BitReverseExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int BitReverseExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void BitReverseExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_BIT_REV);
	this->exp->toBinary(out);
}

void BitReverseExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

AnalyzedType BitReverseExpression::getType(AnalyzeContext* actx) {
	return *this->atype;
}

void BitReverseExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* BitReverseExpression::interpret(VirtualMachine* vm) {
	uint8_t type = this->atype->getType();

	switch (type) {
		case AnalyzedType::TYPE_BYTE:
			return interpret8Bit(vm);
		case AnalyzedType::TYPE_CHAR:
		case AnalyzedType::TYPE_SHORT:
			return interpret16Bit(vm);
		case AnalyzedType::TYPE_LONG:
			return interpret64Bit(vm);
		default:
			break;
	}

	return interpret32Bit(vm);
}

AbstractVmInstance* BitReverseExpression::interpret8Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);

	int8_t result = pinst->getByteValue();
	result = ~result;

	return PrimitiveReference::createByteReference(vm, result);
}

AbstractVmInstance* BitReverseExpression::interpret16Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);

	int16_t result = pinst->getShortValue();
	result = ~result;

	return PrimitiveReference::createShortReference(vm, result);
}

AbstractVmInstance* BitReverseExpression::interpret32Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);

	int32_t result = pinst->getIntValue();
	result = ~result;

	return PrimitiveReference::createIntReference(vm, result);
}

AbstractVmInstance* BitReverseExpression::interpret64Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);

	int64_t result = pinst->getLongValue();
	result = ~result;

	return PrimitiveReference::createLongReference(vm, result);
}


} /* namespace alinous */
