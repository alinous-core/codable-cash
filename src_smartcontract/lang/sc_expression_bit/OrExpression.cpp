/*
 * OrExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression_bit/OrExpression.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "instance/instance_ref/PrimitiveReference.h"


namespace alinous {

OrExpression::OrExpression() : AbstractArithmeticBinaryExpresson(CodeElement::EXP_OR) {
}

OrExpression::~OrExpression() {
}

void OrExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::preAnalyze(actx);
}

void OrExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyzeTypeRef(actx);
}

void OrExpression::analyze(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyze(actx);

	AnalyzedType type = getType(actx);
	if(!type.isPrimitiveInteger()){
		actx->addValidationError(ValidationError::CODE_ARITHMETIC_NON_INTEGER, this, L"Can not use arithmetic operator to non integer value.", {});
	}
}

int OrExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void OrExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_OR);
	AbstractBinaryExpression::toBinary(out);
}

void OrExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

AnalyzedType OrExpression::getType(AnalyzeContext* actx) {
	return *this->atype;
}

AbstractVmInstance* OrExpression::interpret(VirtualMachine* vm) {
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

AbstractVmInstance* OrExpression::interpret8Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int8_t result = pinst->getByteValue();

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		releaser.registerInstance(oinst);

		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		result |= opinst->getByteValue();
	}

	return PrimitiveReference::createByteReference(vm, result);
}

AbstractVmInstance* OrExpression::interpret16Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int16_t result = pinst->getShortValue();

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		releaser.registerInstance(oinst);

		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		result |= opinst->getShortValue();
	}

	return PrimitiveReference::createShortReference(vm, result);
}

AbstractVmInstance* OrExpression::interpret32Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int32_t result = pinst->getIntValue();

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		releaser.registerInstance(oinst);

		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		result |= opinst->getIntValue();
	}

	return PrimitiveReference::createIntReference(vm, result);
}

AbstractVmInstance* OrExpression::interpret64Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int64_t result = pinst->getLongValue();

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		releaser.registerInstance(oinst);

		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		result |= opinst->getLongValue();
	}

	return PrimitiveReference::createLongReference(vm, result);
}

} /* namespace alinous */
