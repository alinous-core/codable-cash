/*
 * PostIncrementExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression_arithmetic/PostIncrementExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"


namespace alinous {

PostIncrementExpression::PostIncrementExpression() : AbstractArithmeticExpression(CodeElement::EXP_POST_INC) {
	this->ope = 0;
}

PostIncrementExpression::~PostIncrementExpression() {
}

void PostIncrementExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractArithmeticExpression::preAnalyze(actx);
}

void PostIncrementExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractArithmeticExpression::analyzeTypeRef(actx);
}

void PostIncrementExpression::analyze(AnalyzeContext* actx) {
	AbstractArithmeticExpression::analyze(actx);

	AnalyzedType type = getType(actx);
	if(!type.isPrimitiveInteger()){
		actx->addValidationError(ValidationError::CODE_ARITHMETIC_NON_INTEGER, this, L"Can not use arithmetic operator to non integer value.", {});
	}
}

void PostIncrementExpression::setOpe(int ope) noexcept {
	this->ope = ope;
}

int PostIncrementExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void PostIncrementExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_POST_INC);
	this->exp->toBinary(out);
}

void PostIncrementExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

AnalyzedType PostIncrementExpression::getType(AnalyzeContext* actx) {
	return *this->atype;
}

void PostIncrementExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* PostIncrementExpression::interpret(VirtualMachine* vm) {
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

AbstractVmInstance* PostIncrementExpression::interpret8Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	uint8_t val = ref->getByteValue();
	PrimitiveReference* lastValue = PrimitiveReference::createByteReference(vm, val);

	if(this->ope == PLUS){
		val = val  + 1;
	}else if(this->ope == MINUS){
		val = val - 1;
	}

	ref->setByteValue(val);

	return lastValue;
}

AbstractVmInstance* PostIncrementExpression::interpret16Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	uint16_t val = ref->getShortValue();
	PrimitiveReference* lastValue = PrimitiveReference::createShortReference(vm, val);

	if(this->ope == PLUS){
		val = val  + 1;
	}else if(this->ope == MINUS){
		val = val - 1;
	}

	ref->setShortValue(val);

	return lastValue;
}

AbstractVmInstance* PostIncrementExpression::interpret32Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	uint32_t val = ref->getIntValue();
	PrimitiveReference* lastValue = PrimitiveReference::createIntReference(vm, val);

	if(this->ope == PLUS){
		val = val  + 1;
	}else if(this->ope == MINUS){
		val = val - 1;
	}

	ref->setIntValue(val);

	return lastValue;
}

AbstractVmInstance* PostIncrementExpression::interpret64Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	uint64_t val = ref->getLongValue();
	PrimitiveReference* lastValue = PrimitiveReference::createLongReference(vm, val);

	if(this->ope == PLUS){
		val = val  + 1;
	}else if(this->ope == MINUS){
		val = val - 1;
	}

	ref->setLongValue(val);

	return lastValue;
}

} /* namespace alinous */
