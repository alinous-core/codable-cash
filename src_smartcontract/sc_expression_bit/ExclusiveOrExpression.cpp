/*
 * ExclusiveOrExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/ExclusiveOrExpression.h"

#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"


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
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
