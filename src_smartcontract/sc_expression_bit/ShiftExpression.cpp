/*
 * ShiftExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/ShiftExpression.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/ValidationError.h"


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
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
