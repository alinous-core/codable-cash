/*
 * ConditionalOrExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_logical/ConditionalOrExpression.h"
#include "sc_analyze/AnalyzedType.h"

namespace alinous {

ConditionalOrExpression::ConditionalOrExpression() : AbstractBinaryExpression(CodeElement::EXP_CND_OR) {
}

ConditionalOrExpression::~ConditionalOrExpression() {
}

void ConditionalOrExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void ConditionalOrExpression::analyzeTypeRef(AnalyzeContext* actx) {
	// FIXME expression : analyze type
}

void ConditionalOrExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);
}

int ConditionalOrExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void ConditionalOrExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_CND_OR);
	AbstractBinaryExpression::toBinary(out);
}

void ConditionalOrExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

AnalyzedType ConditionalOrExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

AbstractVmInstance* ConditionalOrExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
