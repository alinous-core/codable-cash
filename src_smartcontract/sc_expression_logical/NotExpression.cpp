/*
 * NotExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_logical/NotExpression.h"
#include "sc_analyze/AnalyzedType.h"

namespace alinous {

NotExpression::NotExpression() : AbstractExpression(CodeElement::EXP_CND_NOT) {
	this->exp = nullptr;
}

NotExpression::~NotExpression() {
	delete this->exp;
}

void NotExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void NotExpression::analyzeTypeRef(AnalyzeContext* actx) {
	// FIXME expression : analyze type
}

void NotExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
}

void NotExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int NotExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void NotExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_CND_NOT);
	this->exp->toBinary(out);
}

void NotExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

AnalyzedType NotExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void NotExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* NotExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
