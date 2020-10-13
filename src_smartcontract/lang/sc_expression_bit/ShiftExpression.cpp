/*
 * ShiftExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression_bit/ShiftExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/ValidationError.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "instance/instance_ref/PrimitiveReference.h"


namespace alinous {

ShiftExpression::ShiftExpression() : AbstractArithmeticBinaryExpresson(CodeElement::EXP_SHIFT), operations(4) {
}

ShiftExpression::~ShiftExpression() {
}

void ShiftExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::preAnalyze(actx);
}

void ShiftExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyzeTypeRef(actx);
}

void ShiftExpression::analyze(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyze(actx);

	AnalyzedType at = this->list.get(0)->getType(actx);
	if(this->atype != nullptr){
		delete this->atype;
	}
	this->atype = new AnalyzedType(at);

	AnalyzedType type = getType(actx);
	if(!type.isPrimitiveInteger()){
		actx->addValidationError(ValidationError::CODE_ARITHMETIC_NON_INTEGER, this, L"Can not use arithmetic operator to non integer value.", {});
	}
}

void ShiftExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

int ShiftExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		total += sizeof(uint8_t);
	}

	return total;
}

void ShiftExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_SHIFT);
	AbstractBinaryExpression::toBinary(out);

	int maxLoop = this->operations.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);
		out->put(op);
	}
}

void ShiftExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = in->get();
		this->operations.addElement(op);
	}
}

AnalyzedType ShiftExpression::getType(AnalyzeContext* actx) {
	AbstractExpression* first = this->list.get(0);
	return first->getType(actx);
}

AbstractVmInstance* ShiftExpression::interpret(VirtualMachine* vm) {
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

AbstractVmInstance* ShiftExpression::interpret8Bit(VirtualMachine* vm) {
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

		uint8_t op = this->operations.get(0);
		if(op == RIGHT){
			result = result >> opinst->getIntValue();
		}else if(op == LEFT){
			result = result << opinst->getIntValue();
		}
	}

	return PrimitiveReference::createIntReference(vm, result);
}

AbstractVmInstance* ShiftExpression::interpret16Bit(VirtualMachine* vm) {
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

		uint8_t op = this->operations.get(0);
		if(op == RIGHT){
			result = result >> opinst->getIntValue();
		}else if(op == LEFT){
			result = result << opinst->getIntValue();
		}
	}

	return PrimitiveReference::createShortReference(vm, result);
}

AbstractVmInstance* ShiftExpression::interpret32Bit(VirtualMachine* vm) {
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

		uint8_t op = this->operations.get(0);
		if(op == RIGHT){
			result = result >> opinst->getIntValue();
		}else if(op == LEFT){
			result = result << opinst->getIntValue();
		}
	}

	return PrimitiveReference::createIntReference(vm, result);
}

AbstractVmInstance* ShiftExpression::interpret64Bit(VirtualMachine* vm) {
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

		uint8_t op = this->operations.get(0);
		if(op == RIGHT){
			result = result >> opinst->getIntValue();
		}else if(op == LEFT){
			result = result << opinst->getIntValue();
		}
	}

	return PrimitiveReference::createLongReference(vm, result);
}

} /* namespace alinous */
