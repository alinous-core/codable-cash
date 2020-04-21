/*
 * VariableInstractionHolder.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/VariableInstractionHolder.h"

#include "sc_expression/AbstractExpression.h"
#include "sc_expression/VariableIdentifier.h"
#include "sc_expression/ArrayReferenceExpression.h"
#include "sc_expression/FunctionCallExpression.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/ValidationError.h"

#include "variable_access/AbstractVariableInstraction.h"
#include "variable_access/ExpressionAccess.h"
#include "variable_access/ThisPointerAccess.h"
#include "variable_access/ArrayReferenceAccess.h"
#include "variable_access/MemberVariableAccess.h"
#include "variable_access/StackVariableAccess.h"
#include "variable_access/MemberFunctionCallAccess.h"

#include "sc_analyze_stack/AnalyzeStackManager.h"


namespace alinous {

VariableInstractionHolder::VariableInstractionHolder() {
	this->memberAccess = false;
	this->atype = nullptr;
}

VariableInstractionHolder::~VariableInstractionHolder() {
	this->list.deleteElements();
	delete this->atype;
}

void VariableInstractionHolder::addExpression(AbstractExpression* exp, AnalyzeContext* actx) noexcept {
	short kind = exp->getKind();

	switch(kind){
	case CodeElement::EXP_VARIABLE_ID:
		addVariableIdExp(exp, actx);
		break;
	case CodeElement::EXP_ARRAY_REF:
		addArrayReference(exp, actx);
		break;
	case CodeElement::EXP_FUNCTIONCALL:
		addFunctionCallExp(exp, actx);
		break;
	default:
		ExpressionAccess* access = new ExpressionAccess(exp);
		this->list.addElement(access);
		break;
	}
}

void VariableInstractionHolder::addVariableIdExp(AbstractExpression* exp, AnalyzeContext* actx) noexcept {
	AbstractVariableInstraction* instruction = doAddVariableIdExp(exp, actx);

	uint8_t type = instruction->getType();
	if(type == AbstractVariableInstraction::INSTRUCTION_MEMBER_VARIABLE && this->list.isEmpty()){
		ThisPointerAccess* access = new ThisPointerAccess();
		this->list.addElement(access);
		this->memberAccess = true;
	}

	this->list.addElement(instruction);
}


AbstractVariableInstraction* VariableInstractionHolder::doAddVariableIdExp(AbstractExpression* exp, AnalyzeContext* actx) noexcept {
	AbstractVariableInstraction* ret = nullptr;

	VariableIdentifier* valId = dynamic_cast<VariableIdentifier*>(exp);
	assert(valId != nullptr);

	if(valId->isThis()){
		if(this->list.isEmpty()){
			ThisPointerAccess* access = new ThisPointerAccess();

			this->memberAccess = true;
			ret = access;
		}
	}
	else if(!this->memberAccess){ // stack or not
		StackVariableAccess* access = handleStackVariableIdExp(valId, exp, actx);

		if(access != nullptr){
			this->list.addElement(access);
			this->memberAccess = true;
		}
	}
	else{
		ret = new MemberVariableAccess(valId);
	}

	return ret;
}


StackVariableAccess* VariableInstractionHolder::handleStackVariableIdExp(VariableIdentifier* valId, AbstractExpression* exp, AnalyzeContext* actx) noexcept {
	AnalyzeStackManager* stManager = actx->getAnalyzeStackManager();

	const UnicodeString* name = valId->getName();
	StackVariableAccess* access = stManager->findStackVariableAccess(name);

	return access;
}

void VariableInstractionHolder::addArrayReference(AbstractExpression* exp, AnalyzeContext* actx) noexcept {
	ArrayReferenceExpression* arrayRefExp = dynamic_cast<ArrayReferenceExpression*>(exp);
	assert(arrayRefExp != nullptr);

	// FIXME array is stack object or
	AbstractExpression* aexp = arrayRefExp->getExp();
	short elementType = aexp->getKind();



	ArrayReferenceAccess* access = new ArrayReferenceAccess(arrayRefExp);
	this->list.addElement(access);
}

void VariableInstractionHolder::addFunctionCallExp(AbstractExpression* exp,	AnalyzeContext* actx) noexcept {
	FunctionCallExpression* fexp = dynamic_cast<FunctionCallExpression*>(exp);

	MemberFunctionCallAccess* access = new MemberFunctionCallAccess(fexp);
	this->list.addElement(access);
}

void VariableInstractionHolder::analyze(AnalyzeContext* actx, CodeElement* element) {
	AbstractVariableInstraction* lastIinst = nullptr;

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		if(lastIinst != nullptr && checkNotVoid(actx, lastIinst)){
			break;
		}

		AbstractVariableInstraction* inst = this->list.get(i);
		inst->analyze(actx, lastIinst, element);

		if(!inst->hasErrorOnAnalyze()){
			lastIinst = inst;
		}
		else{
			break;
		}
	}

	if(lastIinst != nullptr){
		AnalyzedType at = lastIinst->getAnalyzedType();
		this->atype = new AnalyzedType(at);
	}

}

bool VariableInstractionHolder::checkNotVoid(AnalyzeContext* actx, AbstractVariableInstraction* inst) {
	AnalyzedType at = inst->getAnalyzedType();

	if(at.isVoid()){
		CodeElement* codeElement = inst->getCodeElement();
		FunctionCallExpression* exp = dynamic_cast<FunctionCallExpression*>(codeElement);
		VariableIdentifier* valId = exp->getName();

		actx->addValidationError(ValidationError::CODE_CLASS_MEMBER_VOID, codeElement, L"The '{0}()' is void type and don't have members.", {valId->getName()});
		return true;
	}
	return false;
}


AnalyzedType* VariableInstractionHolder::getAnalyzedType() const noexcept {
	return this->atype;
}

AbstractVmInstance* VariableInstractionHolder::interpret(VirtualMachine* vm) {
	AbstractVmInstance* lastInst = nullptr;

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractVariableInstraction* inst = this->list.get(i);
		lastInst = inst->interpret(vm, lastInst);
	}

	return lastInst;
}

} /* namespace alinous */
