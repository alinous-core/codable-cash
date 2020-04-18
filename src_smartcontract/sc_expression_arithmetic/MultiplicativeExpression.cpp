/*
 * MultiplicativeExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "sc_expression_arithmetic/MultiplicativeExpression.h"

#include "instance_gc/GcManager.h"

#include "instance_ref/PrimitiveReference.h"

#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"

#include "instance_exception/ExceptionInterrupt.h"

namespace alinous {

MultiplicativeExpression::MultiplicativeExpression() : AbstractArithmeticBinaryExpresson(CodeElement::EXP_MUL) {
}

MultiplicativeExpression::~MultiplicativeExpression() {
}

void MultiplicativeExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void MultiplicativeExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyzeTypeRef(actx);
}

void MultiplicativeExpression::analyze(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyze(actx);

	AnalyzedType type = getType(actx);
	if(!type.isPrimitiveInteger()){
		actx->addValidationError(ValidationError::CODE_ARITHMETIC_NON_INTEGER, this, L"Can not use arithmetic operator to non integer value.", {});
	}

	int maxLoop = this->operations.size();
	for(int i = 1; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);

		if(op == MultiplicativeExpression::DIV || op == MultiplicativeExpression::MOD){
			setThrowsException(true);
			break;
		}
	}
}

AbstractVmInstance* MultiplicativeExpression::interpret(VirtualMachine* vm) {
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

AbstractVmInstance* MultiplicativeExpression::interpret8Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	// FIXME exception

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int8_t result = pinst->getByteValue();

	gc->handleFloatingObject(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		uint8_t op = this->operations.get(i - 1);

		if(op == MUL){
			result *= opinst->getByteValue();
		}else if(op == DIV){
			uint8_t v = opinst->getByteValue();
			checkZeroDiv(v, vm);

			result = result / v;
		}else if(op == MOD){
			uint8_t v = opinst->getByteValue();
			checkZeroDiv(v, vm);

			result = result % v;
		}

		gc->handleFloatingObject(opinst);
	}

	return PrimitiveReference::createByteReference(vm, result);
}

AbstractVmInstance* MultiplicativeExpression::interpret16Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int16_t result = pinst->getShortValue();

	gc->handleFloatingObject(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		uint8_t op = this->operations.get(i - 1);

		if(op == MUL){
			result *= opinst->getShortValue();
		}else if(op == DIV){
			int16_t v = opinst->getShortValue();
			checkZeroDiv(v, vm);

			result = result / v;
		}else if(op == MOD){
			int16_t v = opinst->getShortValue();
			checkZeroDiv(v, vm);

			result = result % v;
		}

		gc->handleFloatingObject(opinst);
	}

	return PrimitiveReference::createShortReference(vm, result);
}

AbstractVmInstance* MultiplicativeExpression::interpret32Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int32_t result = pinst->getIntValue();

	gc->handleFloatingObject(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		uint8_t op = this->operations.get(i - 1);

		if(op == MUL){
			result *= opinst->getIntValue();
		}else if(op == DIV){
			int32_t v = opinst->getIntValue();
			checkZeroDiv(v, vm);

			result = result / v;
		}else if(op == MOD){
			int32_t v = opinst->getIntValue();
			checkZeroDiv(v, vm);

			result = result % v;
		}

		gc->handleFloatingObject(opinst);
	}

	return PrimitiveReference::createIntReference(vm, result);
}

AbstractVmInstance* MultiplicativeExpression::interpret64Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int64_t result = pinst->getLongValue();

	gc->handleFloatingObject(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		uint8_t op = this->operations.get(i - 1);

		if(op == MUL){
			result *= opinst->getLongValue();
		}else if(op == DIV){
			int64_t v = opinst->getLongValue();
			checkZeroDiv(v, vm);

			result = result / v;
		}else if(op == MOD){
			int64_t v = opinst->getLongValue();
			checkZeroDiv(v, vm);

			result = result % v;
		}

		gc->handleFloatingObject(opinst);
	}

	return PrimitiveReference::createLongReference(vm, result);
}

void MultiplicativeExpression::checkZeroDiv(int64_t val, VirtualMachine* vm) const {
	if(val == 0){


		ExceptionInterrupt::interruptPoint(vm);
	}
}

} /* namespace alinous */
