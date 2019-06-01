/*
 * ConditionalAndExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_logical/ConditionalAndExpression.h"

namespace alinous {

ConditionalAndExpression::ConditionalAndExpression() : AbstractBinaryExpression(CodeElement::EXP_CND_AND) {
}

ConditionalAndExpression::~ConditionalAndExpression() {
}

void ConditionalAndExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void ConditionalAndExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);
}

int ConditionalAndExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void ConditionalAndExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_CND_AND);
	AbstractBinaryExpression::toBinary(out);
}

void ConditionalAndExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}


} /* namespace alinous */
