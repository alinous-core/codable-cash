/*
 * OrExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/OrExpression.h"
#include "sc_analyze/AnalyzedType.h"

#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"

namespace alinous {

OrExpression::OrExpression() : AbstractArithmeticBinaryExpresson(CodeElement::EXP_OR) {
}

OrExpression::~OrExpression() {
}

void OrExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::preAnalyze(actx);
}

void OrExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyzeTypeRef(actx);
}

void OrExpression::analyze(AnalyzeContext* actx) {
	AbstractArithmeticBinaryExpresson::analyze(actx);

	AnalyzedType type = getType(actx);
	if(!type.isPrimitiveInteger()){
		actx->addValidationError(ValidationError::CODE_ARITHMETIC_NON_INTEGER, this, L"Can not use arithmetic operator to non integer value.", {});
	}
}

int OrExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void OrExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_OR);
	AbstractBinaryExpression::toBinary(out);
}

void OrExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

AnalyzedType OrExpression::getType(AnalyzeContext* actx) {
	return *this->atype;
}

AbstractVmInstance* OrExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
