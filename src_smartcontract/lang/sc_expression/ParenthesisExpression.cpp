/*
 * ParenthesisExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression/ParenthesisExpression.h"
#include "engine/sc_analyze/AnalyzedType.h"

namespace alinous {

ParenthesisExpression::ParenthesisExpression() : AbstractExpression(CodeElement::EXP_PARENTHESIS) {
	this->exp = nullptr;
}

ParenthesisExpression::~ParenthesisExpression() {
	delete this->exp;
}

void ParenthesisExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void ParenthesisExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void ParenthesisExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
}

void ParenthesisExpression::setExp(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int ParenthesisExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void ParenthesisExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_PARENTHESIS);
	this->exp->toBinary(out);
}

void ParenthesisExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

AnalyzedType ParenthesisExpression::getType(AnalyzeContext* actx) {
	return this->exp->getType(actx);
}

void ParenthesisExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* ParenthesisExpression::interpret(VirtualMachine* vm) {
	return this->exp->interpret(vm);
}

} /* namespace alinous */
