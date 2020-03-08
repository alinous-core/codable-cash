/*
 * ExclusiveOrExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/ExclusiveOrExpression.h"

namespace alinous {

ExclusiveOrExpression::ExclusiveOrExpression() : AbstractArithmeticBinaryExpresson(CodeElement::EXP_EX_OR) {
}

ExclusiveOrExpression::~ExclusiveOrExpression() {
}

void ExclusiveOrExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void ExclusiveOrExpression::analyzeTypeRef(AnalyzeContext* actx) {
	// FIXME expression : analyze type
}

void ExclusiveOrExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);

	// FIXME analyze type
}

int ExclusiveOrExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void ExclusiveOrExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_EX_OR);
	AbstractBinaryExpression::toBinary(out);
}

void ExclusiveOrExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

AnalyzedType ExclusiveOrExpression::getType(AnalyzeContext* actx) {
	return *this->atype;
}

AbstractVmInstance* ExclusiveOrExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
