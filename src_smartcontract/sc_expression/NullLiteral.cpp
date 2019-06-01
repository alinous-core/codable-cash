/*
 * NullLiteral.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/NullLiteral.h"

namespace alinous {

NullLiteral::NullLiteral() : AbstractExpression(CodeElement::EXP_NULL_LITERAL) {
}

NullLiteral::~NullLiteral() {
}

void NullLiteral::preAnalyze(AnalyzeContext* actx) {
	// FIXME
}

void NullLiteral::analyze(AnalyzeContext* actx) {
	// FIXME
}

int NullLiteral::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void NullLiteral::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_NULL_LITERAL);
}

void NullLiteral::fromBinary(ByteBuffer* in) {
}


} /* namespace alinous */
