/*
 * JsonKeyValuePair.cpp
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#include "sc_expression_json/JsonKeyValuePairExpression.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "base_io/ByteBuffer.h"
#include "base/UnicodeString.h"

#include "sc_expression/AbstractExpression.h"
#include "sc_expression_literal/LiteralExpression.h"

namespace alinous {

JsonKeyValuePairExpression::JsonKeyValuePairExpression() : AbstractJsonExpression(CodeElement::EXP_JSON_VALUE_PAIR) {
	this->name = nullptr;
	this->value = nullptr;
}

JsonKeyValuePairExpression::~JsonKeyValuePairExpression() {
	delete this->name;
	delete this->value;
}

void JsonKeyValuePairExpression::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void JsonKeyValuePairExpression::setName(LiteralExpression* name) noexcept {
	this->name = name->getStringBody();

	delete name;
}

void JsonKeyValuePairExpression::setValue(AbstractExpression* value) noexcept {
	this->value = value;
}

void JsonKeyValuePairExpression::preAnalyze(AnalyzeContext* actx) {
	this->value->setParent(this);
	this->value->preAnalyze(actx);
}

void JsonKeyValuePairExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->value->analyzeTypeRef(actx);
}

void JsonKeyValuePairExpression::analyze(AnalyzeContext* actx) {
	this->value->analyze(actx);
}

AnalyzedType JsonKeyValuePairExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_DOM_VALUE_PAIR);
}

void JsonKeyValuePairExpression::init(VirtualMachine* vm) {
	this->value->init(vm);
}

AbstractVmInstance* JsonKeyValuePairExpression::interpret(VirtualMachine* vm) {
}

int JsonKeyValuePairExpression::binarySize() const {
}

void JsonKeyValuePairExpression::toBinary(ByteBuffer* out) {
}

void JsonKeyValuePairExpression::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
