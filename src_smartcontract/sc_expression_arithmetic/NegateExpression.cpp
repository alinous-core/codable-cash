/*
 * NegateExpression.cpp
 *
 *  Created on: 2019/02/14
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/NegateExpression.h"
#include "sc_analyze/AnalyzedType.h"

namespace alinous {

NegateExpression::NegateExpression() : AbstractExpression(CodeElement::EXP_NEGATE) {
	this->exp = nullptr;
}

NegateExpression::~NegateExpression() {
	delete this->exp;
}

void NegateExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void NegateExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void NegateExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
}

void NegateExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
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

AnalyzedType NegateExpression::getType() {
	return this->exp->getType();
}

AbstractVmInstance* NegateExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
