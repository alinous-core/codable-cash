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

#include "sc_analyze/AnalyzeContext.h"

#include "variable_access/AbstractVariableInstraction.h"
#include "variable_access/ExpressionAccess.h"
#include "variable_access/ThisPointerAccess.h"
#include "variable_access/ArrayReferenceAccess.h"
#include "variable_access/MemberVariableAccess.h"
#include "variable_access/StackVariableAccess.h"

#include "sc_analyze_stack/AnalyzeStackManager.h"


namespace alinous {

VariableInstractionHolder::VariableInstractionHolder() {
	this->memberAccess = false;
}

VariableInstractionHolder::~VariableInstractionHolder() {
	this->list.deleteElements();
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
	VariableIdentifier* valId = dynamic_cast<VariableIdentifier*>(exp);
	assert(valId != nullptr);

	if(valId->isThis()){
		if(this->list.isEmpty()){
			ThisPointerAccess* access = new ThisPointerAccess();

			this->list.addElement(access);
			this->memberAccess = true;
		}
		return;
	}

	// stack or not
	if(!this->memberAccess){
		if(handleStackVariableIdExp(valId, exp, actx)){
			return;
		}
	}

	// member access
	if(this->list.isEmpty()){
		ThisPointerAccess* access = new ThisPointerAccess();
		this->list.addElement(access);
		this->memberAccess = true;
	}

	MemberVariableAccess* access = new MemberVariableAccess(valId);
	this->list.addElement(access);
}

bool VariableInstractionHolder::handleStackVariableIdExp(VariableIdentifier* valId, AbstractExpression* exp, AnalyzeContext* actx) noexcept {
	AnalyzeStackManager* stManager = actx->getAnalyzeStackManager();

	UnicodeString* name = valId->getName();
	StackVariableAccess* access = stManager->findStackVariableAccess(name);
	if(access != nullptr){
		this->list.addElement(access);
		return true;
	}

	return false;
}

void VariableInstractionHolder::addArrayReference(AbstractExpression* exp, AnalyzeContext* actx) noexcept {
	ArrayReferenceExpression* arrayRefExp = dynamic_cast<ArrayReferenceExpression*>(exp);
	assert(arrayRefExp != nullptr);

	// FIXME array is stack object or

	ArrayReferenceAccess* access = new ArrayReferenceAccess(arrayRefExp);
	this->list.addElement(access);
}

void VariableInstractionHolder::addFunctionCallExp(AbstractExpression* exp,	AnalyzeContext* actx) noexcept {
	// FIXME array is stack object or
}

void VariableInstractionHolder::analyze(AnalyzeContext* actx) {
	AbstractVariableInstraction* lastIinst = nullptr;

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractVariableInstraction* inst = this->list.get(i);
		inst->analyze(actx, lastIinst);

		lastIinst = inst;
	}

	this->atype = lastIinst->getAnalyzedType();
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
