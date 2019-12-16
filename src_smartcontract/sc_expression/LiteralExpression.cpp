/*
 * LiteralExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/LiteralExpression.h"
#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedType.h"
namespace alinous {

LiteralExpression::LiteralExpression() : AbstractExpression(CodeElement::EXP_LITERAL){
	this->str = nullptr;
	this->dquote = true;
}

LiteralExpression::~LiteralExpression() {
	delete this->str;
}

void LiteralExpression::preAnalyze(AnalyzeContext* actx) {

}

void LiteralExpression::analyzeTypeRef(AnalyzeContext* actx) {
	// FIXME expression : analyze type
}

void LiteralExpression::analyze(AnalyzeContext* actx) {

}

void LiteralExpression::setString(UnicodeString* str, bool dquote) noexcept {
	this->str = str;
	this->dquote = dquote;
}

int LiteralExpression::binarySize() const {
	checkNotNull(this->str);

	int total = sizeof(uint16_t);
	total += sizeof(uint8_t);
	total += stringSize(this->str);

	return total;
}

void LiteralExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_LITERAL);

	out->put(this->dquote ? 1 : 0);
	putString(out, this->str);
}

void LiteralExpression::fromBinary(ByteBuffer* in) {
	char bl = in->get();
	this->dquote = (bl == 1);
	this->str = getString(in);
}

AnalyzedType LiteralExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_STRING);
}

void LiteralExpression::init(VirtualMachine* vm) {
	// FIXME const literal
}

AbstractVmInstance* LiteralExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
