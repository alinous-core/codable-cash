/*
 * VariableIdentifier.cpp
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#include "sc_expression/VariableIdentifier.h"
#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"

#include "sc_analyze_stack/AnalyzeStackManager.h"

#include "variable_access/AbstractVariableInstraction.h"

namespace alinous {

const UnicodeString VariableIdentifier::__THIS(L"this");

VariableIdentifier::VariableIdentifier() : AbstractExpression(CodeElement::EXP_VARIABLE_ID) {
	this->name = nullptr;
	this->access = nullptr;
	this->executable = false;
}

VariableIdentifier::~VariableIdentifier() {
	delete this->name;
	delete this->access;
}

void VariableIdentifier::preAnalyze(AnalyzeContext* actx) {

}

void VariableIdentifier::analyzeTypeRef(AnalyzeContext* actx) {
	CodeElement* p = getParent();
	this->executable = p->isExecutable();
}

void VariableIdentifier::analyze(AnalyzeContext* actx) {
	AnalyzeStackManager* stack = actx->getAnalyzeStackManager();
	stack->findStackVariableAccess(this->name);

}

void VariableIdentifier::setName(UnicodeString* name) noexcept {
	this->name = name;
}

const UnicodeString* alinous::VariableIdentifier::getName() const noexcept {
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

AnalyzedType VariableIdentifier::getType(AnalyzeContext* actx) {
	// FIXME analyze variable id type
	return AnalyzedType();
}

void VariableIdentifier::init(VirtualMachine* vm) {
}

AbstractVmInstance* VariableIdentifier::interpret(VirtualMachine* vm) {
	// FIXME interpret
	return nullptr;
}

bool VariableIdentifier::isThis() const noexcept {
	return __THIS.equals(this->name);
}


} /* namespace alinous */
