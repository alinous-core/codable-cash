/*
 * OrExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/OrExpression.h"
#include "sc_analyze/AnalyzedType.h"

namespace alinous {

OrExpression::OrExpression() : AbstractBinaryExpression(CodeElement::EXP_OR) {
}

OrExpression::~OrExpression() {
}

void OrExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void OrExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);

	// FIXME analyze type
}

int OrExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void OrExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_OR);
	AbstractBinaryExpression::toBinary(out);
}

void OrExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

AnalyzedType OrExpression::getType() {
	return this->atype;
}

AbstractVmInstance* OrExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
