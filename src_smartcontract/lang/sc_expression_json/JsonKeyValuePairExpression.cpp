/*
 * JsonKeyValuePair.cpp
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#include "lang/sc_expression_json/JsonKeyValuePairExpression.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "base_io/ByteBuffer.h"
#include "base/UnicodeString.h"

#include "lang/sc_expression/AbstractExpression.h"
#include "lang/sc_expression_literal/LiteralExpression.h"

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
	return this->value->interpret(vm);
}

int JsonKeyValuePairExpression::binarySize() const {
	checkNotNull(this->name);
	checkNotNull(this->value);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);
	total += this->value->binarySize();

	return total;
}

void JsonKeyValuePairExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);
	checkNotNull(this->value);

	out->putShort(CodeElement::EXP_JSON_VALUE_PAIR);
	putString(out, this->name);
	this->value->toBinary(out);
}

void JsonKeyValuePairExpression::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	CodeElement* element = CodeElement::createFromBinary(in);
	checkIsExp(element);

	this->value = dynamic_cast<AbstractExpression*>(element);
}

const UnicodeString* JsonKeyValuePairExpression::getName() const noexcept {
	return this->name;
}

} /* namespace alinous */
