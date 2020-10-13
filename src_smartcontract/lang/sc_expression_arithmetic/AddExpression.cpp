/*
 * AddExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "lang/sc_expression_arithmetic/AddExpression.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"

namespace alinous {

AddExpression::AddExpression() : AbstractArithmeticBinaryExpresson(CodeElement::EXP_ADD) {
}

AddExpression::~AddExpression() {
}

void AddExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void AddExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyzeTypeRef(actx);
}

void AddExpression::analyze(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyze(actx);
}


AbstractVmInstance* AddExpression::interpret(VirtualMachine* vm) {
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

AbstractVmInstance* AddExpression::interpret8Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int8_t result = pinst->getByteValue();

	releaser.registerInstance(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		releaser.registerInstance(oinst);

		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		uint8_t op = this->operations.get(i - 1);

		if(op == ADD){
			result += opinst->getByteValue();
		}else if(op == SUB){
			result -= opinst->getByteValue();
		}
	}

	return PrimitiveReference::createByteReference(vm, result);
}

AbstractVmInstance* AddExpression::interpret16Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int16_t result = pinst->getShortValue();

	releaser.registerInstance(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		releaser.registerInstance(oinst);

		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		uint8_t op = this->operations.get(i - 1);

		if(op == ADD){
			result += opinst->getShortValue();
		}else if(op == SUB){
			result -= opinst->getShortValue();
		}
	}

	return PrimitiveReference::createShortReference(vm, result);
}

AbstractVmInstance* AddExpression::interpret32Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int32_t result = pinst->getIntValue();

	releaser.registerInstance(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		releaser.registerInstance(oinst);

		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		uint8_t op = this->operations.get(i - 1);
		if(op == ADD){
			result += opinst->getIntValue();
		}else if(op == SUB){
			result -= opinst->getIntValue();
		}
	}

	return PrimitiveReference::createIntReference(vm, result);
}

AbstractVmInstance* AddExpression::interpret64Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int64_t result = pinst->getLongValue();

	releaser.registerInstance(pinst);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		releaser.registerInstance(oinst);

		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(oinst);

		uint8_t op = this->operations.get(i - 1);
		if(op == ADD){
			result += opinst->getLongValue();
		}else if(op == SUB){
			result -= opinst->getLongValue();
		}
	}

	return PrimitiveReference::createLongReference(vm, result);
}

} /* namespace alinous */
