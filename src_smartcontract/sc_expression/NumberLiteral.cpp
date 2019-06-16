/*
 * NumberLiteral.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/NumberLiteral.h"
#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedType.h"

namespace alinous {

NumberLiteral::NumberLiteral() : AbstractExpression(CodeElement::EXP_NUMBER_LITERAL) {
	this->str = nullptr;
}

NumberLiteral::~NumberLiteral() {
	delete this->str;
}

void NumberLiteral::preAnalyze(AnalyzeContext* actx) {

}

void NumberLiteral::analyzeType(AnalyzeContext* actx) {
}


void NumberLiteral::analyze(AnalyzeContext* actx) {
}

void NumberLiteral::setValue(UnicodeString* str) noexcept {
	this->str = str;
}

int NumberLiteral::binarySize() const {
	checkNotNull(this->str);

	int total = sizeof(uint16_t);
	total += stringSize(this->str);

	return total;
}

void NumberLiteral::toBinary(ByteBuffer* out) {
	checkNotNull(this->str);

	out->putShort(CodeElement::EXP_NUMBER_LITERAL);
	putString(out, this->str);
}

void NumberLiteral::fromBinary(ByteBuffer* in) {
	this->str = getString(in);
}

AnalyzedType NumberLiteral::getType() {
	return AnalyzedType(AnalyzedType::TYPE_LONG);
}

AbstractVmInstance* NumberLiteral::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
