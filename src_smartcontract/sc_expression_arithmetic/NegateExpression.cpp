/*
 * NegateExpression.cpp
 *
 *  Created on: 2019/02/14
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/NegateExpression.h"
#include "sc_analyze/AnalyzedType.h"

#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"

#include "instance_ref/PrimitiveReference.h"


namespace alinous {

NegateExpression::NegateExpression() : AbstractArithmeticExpression(CodeElement::EXP_NEGATE) {
}

NegateExpression::~NegateExpression() {

}

void NegateExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractArithmeticExpression::preAnalyze(actx);
}

void NegateExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractArithmeticExpression::analyzeTypeRef(actx);
}

void NegateExpression::analyze(AnalyzeContext* actx) {
	AbstractArithmeticExpression::analyze(actx);

	AnalyzedType type = getType(actx);
	if(!type.isPrimitiveInteger()){
		actx->addValidationError(ValidationError::CODE_ARITHMETIC_NON_INTEGER, this, L"Can not use arithmetic operator to non integer value.", {});
	}
}

int NegateExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void NegateExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_NEGATE);
	this->exp->toBinary(out);
}

void NegateExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

AnalyzedType NegateExpression::getType(AnalyzeContext* actx) {
	return *this->atype;
}

void NegateExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* NegateExpression::interpret(VirtualMachine* vm) {
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

AbstractVmInstance* NegateExpression::interpret8Bit(VirtualMachine* vm) {
	AbstractVmInstance* inst = this->exp->interpret(vm); // FIXME exception
	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	int8_t val = ref->getByteValue() * -1;
	PrimitiveReference* retValue = PrimitiveReference::createByteReference(vm, val);

	return retValue;
}

AbstractVmInstance* NegateExpression::interpret16Bit(VirtualMachine* vm) {
	AbstractVmInstance* inst = this->exp->interpret(vm);
	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	int16_t val = ref->getShortValue() * -1;
	PrimitiveReference* retValue = PrimitiveReference::createShortReference(vm, val);

	return retValue;
}

AbstractVmInstance* NegateExpression::interpret32Bit(VirtualMachine* vm) {
	AbstractVmInstance* inst = this->exp->interpret(vm);
	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	int32_t val = ref->getIntValue() * -1;
	PrimitiveReference* retValue = PrimitiveReference::createIntReference(vm, val);

	return retValue;
}

AbstractVmInstance* NegateExpression::interpret64Bit(VirtualMachine* vm) {
	AbstractVmInstance* inst = this->exp->interpret(vm);
	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

	int64_t val = ref->getLongValue() * -1;
	PrimitiveReference* retValue = PrimitiveReference::createLongReference(vm, val);

	return retValue;
}

} /* namespace alinous */
