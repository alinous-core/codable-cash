/*
 * ExclusiveOrExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/ExclusiveOrExpression.h"

#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"

#include "instance_gc/GcManager.h"

#include "instance_ref/PrimitiveReference.h"


namespace alinous {

ExclusiveOrExpression::ExclusiveOrExpression() : AbstractArithmeticBinaryExpresson(CodeElement::EXP_EX_OR) {
}

ExclusiveOrExpression::~ExclusiveOrExpression() {
}

void ExclusiveOrExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::preAnalyze(actx);
}

void ExclusiveOrExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyzeTypeRef(actx);
}

void ExclusiveOrExpression::analyze(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyze(actx);

	AnalyzedType type = getType(actx);
	if(!type.isPrimitiveInteger()){
		actx->addValidationError(ValidationError::CODE_ARITHMETIC_NON_INTEGER, this, L"Can not use arithmetic operator to non integer value.", {});
	}
}

int ExclusiveOrExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void ExclusiveOrExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_EX_OR);
	AbstractBinaryExpression::toBinary(out);
}

void ExclusiveOrExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

AnalyzedType ExclusiveOrExpression::getType(AnalyzeContext* actx) {
	return *this->atype;
}

AbstractVmInstance* ExclusiveOrExpression::interpret(VirtualMachine* vm) {
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

AbstractVmInstance* ExclusiveOrExpression::interpret8Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int8_t result = pinst->getByteValue();

	gc->handleFloatingObject(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		result ^= opinst->getByteValue();

		gc->handleFloatingObject(opinst);
	}

	return PrimitiveReference::createByteReference(vm, result);
}

AbstractVmInstance* ExclusiveOrExpression::interpret16Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int16_t result = pinst->getShortValue();

	gc->handleFloatingObject(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		result &= opinst->getShortValue();

		gc->handleFloatingObject(opinst);
	}

	return PrimitiveReference::createShortReference(vm, result);
}

AbstractVmInstance* ExclusiveOrExpression::interpret32Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int32_t result = pinst->getIntValue();

	gc->handleFloatingObject(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		result ^= opinst->getIntValue();

		gc->handleFloatingObject(opinst);
	}

	return PrimitiveReference::createIntReference(vm, result);
}

AbstractVmInstance* ExclusiveOrExpression::interpret64Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int64_t result = pinst->getLongValue();

	gc->handleFloatingObject(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		result &= opinst->getLongValue();

		gc->handleFloatingObject(opinst);
	}

	return PrimitiveReference::createLongReference(vm, result);
}

} /* namespace alinous */
