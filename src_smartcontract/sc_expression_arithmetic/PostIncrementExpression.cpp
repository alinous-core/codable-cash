/*
 * PostIncrementExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/PostIncrementExpression.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"


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
	return this->exp->getType(actx);
}

void PostIncrementExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* PostIncrementExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
