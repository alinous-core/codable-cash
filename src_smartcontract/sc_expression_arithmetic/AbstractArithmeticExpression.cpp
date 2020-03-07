/*
 * AbstractArithmeticExpression.cpp
 *
 *  Created on: 2020/03/07
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/AbstractArithmeticExpression.h"

namespace alinous {

AbstractArithmeticExpression::AbstractArithmeticExpression(int kind) : AbstractExpression(kind){
	this->exp = nullptr;
}

AbstractArithmeticExpression::~AbstractArithmeticExpression() {
	delete this->exp;
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
}

void AbstractArithmeticExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}


} /* namespace alinous */
