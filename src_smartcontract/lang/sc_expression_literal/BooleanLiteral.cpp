/*
 * BooleanLiteral.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression_literal/BooleanLiteral.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_ref/PrimitiveReference.h"

namespace alinous {

BooleanLiteral::BooleanLiteral() : AbstractExpression(CodeElement::EXP_BOOLEAN_LITERAL) {
	this->value = false;
}

BooleanLiteral::~BooleanLiteral() {
}

void BooleanLiteral::preAnalyze(AnalyzeContext* actx) {

}

void BooleanLiteral::analyzeTypeRef(AnalyzeContext* actx) {
}

void BooleanLiteral::analyze(AnalyzeContext* actx) {

}

void BooleanLiteral::setValue(bool v) noexcept {
	this->value = v;
}

int BooleanLiteral::binarySize() const {
	int total = sizeof(uint16_t);
	total += sizeof(uint8_t);

	return total;
}

void BooleanLiteral::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_BOOLEAN_LITERAL);
	out->put(this->value ? 1 : 0);
}

void BooleanLiteral::fromBinary(ByteBuffer* in) {
	char val = in->get();
	this->value = (val == 1);
}

AnalyzedType BooleanLiteral::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void BooleanLiteral::init(VirtualMachine* vm) {
}

AbstractVmInstance* BooleanLiteral::interpret(VirtualMachine* vm) {
	return PrimitiveReference::createBoolReference(vm, this->value ? 1 : 0);
}

} /* namespace alinous */
