/*
 * AndExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/AndExpression.h"

namespace alinous {

AndExpression::AndExpression() : AbstractBinaryExpression(CodeElement::EXP_AND) {
}

AndExpression::~AndExpression() {
}

void AndExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void AndExpression::analyzeTypeRef(AnalyzeContext* actx) {
	// FIXME expression : analyze type
}

void AndExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);

	// FIXME analyze type
}

AbstractVmInstance* AndExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

int AndExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void AndExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_AND);
	AbstractBinaryExpression::toBinary(out);
}

void AndExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

AnalyzedType AndExpression::getType(AnalyzeContext* actx) {
	return this->atype;
}

} /* namespace alinous */
