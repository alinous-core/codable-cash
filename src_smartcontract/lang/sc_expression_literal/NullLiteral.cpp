/*
 * NullLiteral.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression_literal/NullLiteral.h"
#include "engine/sc_analyze/AnalyzedType.h"

namespace alinous {

NullLiteral::NullLiteral() : AbstractExpression(CodeElement::EXP_NULL_LITERAL) {
}

NullLiteral::~NullLiteral() {
}

void NullLiteral::preAnalyze(AnalyzeContext* actx) {

}

void NullLiteral::analyzeTypeRef(AnalyzeContext* actx) {
}


void NullLiteral::analyze(AnalyzeContext* actx) {

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

AnalyzedType NullLiteral::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_NULL);
}

void NullLiteral::init(VirtualMachine* vm) {

}

AbstractVmInstance* NullLiteral::interpret(VirtualMachine* vm) {
	return nullptr;
}

} /* namespace alinous */
