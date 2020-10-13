/*
 * AbstractArithmeticExpression.cpp
 *
 *  Created on: 2020/03/07
 *      Author: iizuka
 */

#include "lang/sc_expression_arithmetic/AbstractArithmeticExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"


namespace alinous {

AbstractArithmeticExpression::AbstractArithmeticExpression(int kind) : AbstractExpression(kind){
	this->exp = nullptr;
	this->atype = nullptr;
}

AbstractArithmeticExpression::~AbstractArithmeticExpression() {
	delete this->exp;
	delete this->atype;
}

void AbstractArithmeticExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void AbstractArithmeticExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void AbstractArithmeticExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);

	AnalyzedType at = this->exp->getType(actx);
	this->atype = new AnalyzedType(at);
}

void AbstractArithmeticExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}


} /* namespace alinous */
