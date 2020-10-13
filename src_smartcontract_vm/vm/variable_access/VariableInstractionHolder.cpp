/*
 * VariableInstractionHolder.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "vm/variable_access/VariableInstractionHolder.h"

#include "lang/sc_expression/AbstractExpression.h"
#include "lang/sc_expression/VariableIdentifier.h"
#include "lang/sc_expression/ArrayReferenceExpression.h"
#include "lang/sc_expression/FunctionCallExpression.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/TypeResolver.h"

#include "vm/variable_access/AbstractVariableInstraction.h"
#include "vm/variable_access/ExpressionAccess.h"
#include "vm/variable_access/ThisPointerAccess.h"
#include "vm/variable_access/ArrayReferenceAccess.h"
#include "vm/variable_access/MemberVariableAccess.h"
#include "vm/variable_access/StackVariableAccess.h"
#include "vm/variable_access/MemberFunctionCallAccess.h"
#include "vm/variable_access/ClassTypeAccess.h"

#include "engine/sc_analyze_stack/AnalyzeStackManager.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "vm/VirtualMachine.h"

#include "base/StackRelease.h"


namespace alinous {

VariableInstractionHolder::VariableInstractionHolder() {
	this->memberAccess = false;
	this->atype = nullptr;
}

VariableInstractionHolder::~VariableInstractionHolder() {
	this->list.deleteElements();
	delete this->atype;
}

void VariableInstractionHolder::addFirstClassIdentifier(const AnalyzedType* atp) noexcept {
	this->memberAccess = true;
	ClassTypeAccess* access = new ClassTypeAccess(atp);

	this->list.addElement(access);
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
			this->memberAccess = true;
			ret = access;
		}
		else{
			ret = detectNonStackInstruction(valId, actx);
		}
	}
	else{
		ret = new MemberVariableAccess(valId);
	}

	return ret;
}

AbstractVariableInstraction* VariableInstractionHolder::detectNonStackInstruction(VariableIdentifier* valId, AnalyzeContext* actx) noexcept {
	if(valId->isSuper()){
		return handleSuper(valId, actx);
	}

	TypeResolver* resolver = actx->getTypeResolver();

	const UnicodeString* idName = valId->getName();
	AnalyzedType* atp = resolver->findClassType(valId, idName); __STP(atp);

	if(atp != nullptr){
		this->memberAccess = true;
		return new ClassTypeAccess(atp);
	}

	this->memberAccess = true;
	return new MemberVariableAccess(valId);
}

AbstractVariableInstraction* VariableInstractionHolder::handleSuper(VariableIdentifier* valId, AnalyzeContext* actx) noexcept {
	ClassTypeAccess* inst = new ClassTypeAccess(valId);

	return inst;
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

	AbstractExpression* aexp = arrayRefExp->getExp();
	AbstractVariableInstraction* expAccess = doAddVariableIdExp(aexp, actx);

	ArrayReferenceAccess* access = new ArrayReferenceAccess(arrayRefExp);
	access->setExpressionAccess(expAccess);


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
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* lastInst = nullptr;

	int maxLoop = this->list.size();
	int lastLoop = maxLoop - 1;
	for(int i = 0; i != maxLoop; ++i){
		AbstractVariableInstraction* inst = this->list.get(i);
		lastInst = inst->interpret(vm, lastInst);

		if(i != lastLoop){
			releaser.registerInstance(lastInst);
		}
	}

	return lastInst;
}

} /* namespace alinous */
