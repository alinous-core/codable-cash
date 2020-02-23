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
#include "variable_access/StackVariableAccess.h"
#include "variable_access/MemberVariableAccess.h"
#include "variable_access/ThisPointerAccess.h"

#include "instance_ref/AbstractReference.h"

#include "sc_analyze/AnalyzedClass.h"

#include "sc_analyze_functions/VTableRegistory.h"
#include "sc_analyze_functions/VTableClassEntry.h"

#include "sc_analyze_variables/MemberVariableTable.h"

#include "sc_analyze/ValidationError.h"

namespace alinous {

const UnicodeString VariableIdentifier::__THIS(L"this");

VariableIdentifier::VariableIdentifier() : AbstractExpression(CodeElement::EXP_VARIABLE_ID) {
	this->name = nullptr;
	this->thisAccess = nullptr;
	this->access = nullptr;
	this->executable = false;
}

VariableIdentifier::~VariableIdentifier() {
	delete this->name;
	delete this->thisAccess;
	delete this->access;
}

void VariableIdentifier::preAnalyze(AnalyzeContext* actx) {

}

void VariableIdentifier::analyzeTypeRef(AnalyzeContext* actx) {
	CodeElement* p = getParent();
	this->executable = p->isExecutable();
}

void VariableIdentifier::analyze(AnalyzeContext* actx) {
	if(this->executable){
		doAnalyze(actx);
	}
}

void VariableIdentifier::doAnalyze(AnalyzeContext* actx) {
	AnalyzeStackManager* stack = actx->getAnalyzeStackManager();
	this->access = stack->findStackVariableAccess(this->name);

	if(this->access != nullptr){
		this->access->analyze(actx, nullptr, this);
		return;
	}


	MemberVariableAccess* memAccess = new MemberVariableAccess(this);
	this->access = memAccess;

	this->thisAccess = new ThisPointerAccess();

	this->thisAccess->analyze(actx, nullptr, this);
	memAccess->analyze(actx, this->thisAccess, this);

	if(memAccess->hasErrorOnAnalyze()){
		delete this->access;
		delete this->thisAccess;

		this->access = nullptr;
		this->thisAccess = nullptr;

		actx->addValidationError(ValidationError::CODE_CLASS_MEMBER_AND_STACK_VARIABLE_DO_NOT_EXISTS, this, L"Variable for the identifier '{0}' does not exists.", {this->name});
		return;
	}
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
	return this->access->getAnalyzedType();
}

void VariableIdentifier::init(VirtualMachine* vm) {
}

AbstractVmInstance* VariableIdentifier::interpret(VirtualMachine* vm) {
	AbstractVmInstance* lastInst = nullptr;

	if(this->thisAccess != nullptr){
		this->thisAccess->interpret(vm, nullptr);
	}

	AbstractVmInstance* instOrRef = this->access->interpret(vm, lastInst);

	return instOrRef;
}

bool VariableIdentifier::isThis() const noexcept {
	return __THIS.equals(this->name);
}


} /* namespace alinous */
