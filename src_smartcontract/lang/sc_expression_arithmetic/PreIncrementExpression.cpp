/*
 * PreIncrementExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression_arithmetic/PreIncrementExpression.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"


namespace alinous {

PreIncrementExpression::PreIncrementExpression() : AbstractArithmeticExpression(CodeElement::EXP_PRE_INC) {
	this->ope = 0;
}

PreIncrementExpression::~PreIncrementExpression() {

}

void PreIncrementExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractArithmeticExpression::preAnalyze(actx);
}

void alinous::PreIncrementExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractArithmeticExpression::analyzeTypeRef(actx);
}

void PreIncrementExpression::analyze(AnalyzeContext* actx) {
	AbstractArithmeticExpression::analyze(actx);

	AnalyzedType type = getType(actx);
	if(!type.isPrimitiveInteger()){
		actx->addValidationError(ValidationError::CODE_ARITHMETIC_NON_INTEGER, this, L"Can not use arithmetic operator to non integer value.", {});
	}
}

void PreIncrementExpression::setOpe(int ope) noexcept {
	this->ope = ope;
}

int PreIncrementExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void PreIncrementExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_PRE_INC);
	this->exp->toBinary(out);
}

void PreIncrementExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

AnalyzedType PreIncrementExpression::getType(AnalyzeContext* actx) {
	return this->exp->getType(actx);
}

void PreIncrementExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* PreIncrementExpression::interpret(VirtualMachine* vm) {
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

AbstractVmInstance* PreIncrementExpression::interpret8Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	int8_t val = 0;

	if(this->ope == PLUS){
		val = ref->getByteValue() + 1;
	}else if(this->ope == MINUS){
		val = ref->getByteValue() - 1;
	}

	ref->setByteValue(val);

	return ref;

}

AbstractVmInstance* PreIncrementExpression::interpret16Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	int16_t val = 0;

	if(this->ope == PLUS){
		val = ref->getShortValue() + 1;
	}else if(this->ope == MINUS){
		val = ref->getShortValue() - 1;
	}

	ref->setShortValue(val);

	return ref;
}

AbstractVmInstance* PreIncrementExpression::interpret32Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	int32_t val = 0;

	if(this->ope == PLUS){
		val = ref->getIntValue() + 1;
	}else if(this->ope == MINUS){
		val = ref->getIntValue() - 1;
	}

	ref->setIntValue(val);

	return ref;
}

AbstractVmInstance* PreIncrementExpression::interpret64Bit(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	uint64_t val = 0;

	if(this->ope == PLUS){
		val = ref->getLongValue() + 1;
	}else if(this->ope == MINUS){
		val = ref->getLongValue() - 1;
	}

	ref->setLongValue(val);

	return ref;
}

} /* namespace alinous */
