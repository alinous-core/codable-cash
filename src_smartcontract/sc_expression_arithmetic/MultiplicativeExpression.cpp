/*
 * MultiplicativeExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "sc_expression_arithmetic/MultiplicativeExpression.h"


namespace alinous {

MultiplicativeExpression::MultiplicativeExpression() : AbstractArithmeticBinaryExpresson(CodeElement::EXP_MUL) {
}

MultiplicativeExpression::~MultiplicativeExpression() {
}

void MultiplicativeExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void MultiplicativeExpression::analyzeTypeRef(AnalyzeContext* actx) {
	// FIXME expression : analyze type
}

void MultiplicativeExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);

	// FIXME analyze type
}

AbstractVmInstance* MultiplicativeExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
