/*
 * NullLiteral.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/NullLiteral.h"
#include "sc_analyze/AnalyzedType.h"

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

AnalyzedType NullLiteral::getType() {
	return AnalyzedType(AnalyzedType::TYPE_NULL);
}

AbstractVmInstance* NullLiteral::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
