/*
 * VariableIdentifier.cpp
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#include "sc_expression/VariableIdentifier.h"
#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedType.h"

namespace alinous {

const UnicodeString VariableIdentifier::__THIS(L"this");

VariableIdentifier::VariableIdentifier() : AbstractExpression(CodeElement::EXP_VARIABLE_ID) {
	this->name = nullptr;
}

VariableIdentifier::~VariableIdentifier() {
	delete this->name;
}

void VariableIdentifier::preAnalyze(AnalyzeContext* actx) {

}

void VariableIdentifier::analyzeTypeRef(AnalyzeContext* actx) {
}

void VariableIdentifier::analyze(AnalyzeContext* actx) {

}

void VariableIdentifier::setName(UnicodeString* name) noexcept {
	this->name = name;
}

UnicodeString* alinous::VariableIdentifier::getName() const noexcept {
	return this->name;
}

int VariableIdentifier::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);

	return total;
}

void VariableIdentifier::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::EXP_VARIABLE_ID);
	putString(out, this->name);
}

void VariableIdentifier::fromBinary(ByteBuffer* in) {
	this->name = getString(in);
}


AnalyzedType VariableIdentifier::getType() {
	// FIXME analyze variable id type
	return AnalyzedType();
}

AbstractVmInstance* VariableIdentifier::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}


bool VariableIdentifier::isThis() const noexcept {
	return __THIS.equals(this->name);
}


} /* namespace alinous */
