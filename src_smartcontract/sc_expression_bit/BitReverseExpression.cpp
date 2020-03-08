/*
 * BitReverseExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/BitReverseExpression.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/ValidationError.h"


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
}

AbstractVmInstance* BitReverseExpression::interpret16Bit(VirtualMachine* vm) {
}

AbstractVmInstance* BitReverseExpression::interpret32Bit(VirtualMachine* vm) {
}

AbstractVmInstance* BitReverseExpression::interpret64Bit(VirtualMachine* vm) {
}


} /* namespace alinous */
