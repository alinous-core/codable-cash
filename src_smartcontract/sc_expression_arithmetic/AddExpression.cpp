/*
 * AddExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "sc_expression_arithmetic/AddExpression.h"

#include "instance_ref/PrimitiveReference.h"

#include "instance_gc/GcManager.h"
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
	AbstractBinaryExpression::analyze(actx);
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
}

AbstractVmInstance* AddExpression::interpret16Bit(VirtualMachine* vm) {
}

AbstractVmInstance* AddExpression::interpret32Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	AbstractVmInstance* inst = this->list.get(0)->interpret(vm);
	PrimitiveReference* pinst = dynamic_cast<PrimitiveReference*>(inst);
	int32_t result = pinst->getIntValue();

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractVmInstance* oinst = this->list.get(i)->interpret(vm);
		PrimitiveReference* opinst = dynamic_cast<PrimitiveReference*>(inst);

		uint8_t op = this->operations.get(i - 1);
		if(op == ADD){
			result += opinst->getIntValue();
		}else if(op == SUB){
			result -= opinst->getIntValue();
		}

		gc->handleFloatingObject(opinst);
	}

}

AbstractVmInstance* AddExpression::interpret64Bit(VirtualMachine* vm) {
}

} /* namespace alinous */
