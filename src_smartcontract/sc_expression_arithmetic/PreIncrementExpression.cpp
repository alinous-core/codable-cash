/*
 * PreIncrementExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/PreIncrementExpression.h"
#include "sc_analyze/AnalyzedType.h"

#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"


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
	return this->exp->interpret(vm);
}

} /* namespace alinous */
