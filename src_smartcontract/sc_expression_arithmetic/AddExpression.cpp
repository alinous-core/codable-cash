/*
 * AddExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "sc_expression_arithmetic/AddExpression.h"


namespace alinous {

AddExpression::AddExpression() : AbstractArithmeticBinaryExpresson(CodeElement::EXP_ADD) {
}

AddExpression::~AddExpression() {
}

void AddExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void AddExpression::analyzeTypeRef(AnalyzeContext* actx) {
	// FIXME expression : analyze type
}

void AddExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);

	// FIXME analyze type
}

void AddExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}



AbstractVmInstance* AddExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
