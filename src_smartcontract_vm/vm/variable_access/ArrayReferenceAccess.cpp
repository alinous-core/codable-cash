/*
 * ArrayReferenceAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "vm/variable_access/ArrayReferenceAccess.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/ValidationError.h"

#include "lang/sc_expression/ArrayReferenceExpression.h"

#include "instance/instance_array/VmArrayInstanceUtils.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"
#include "instance/instance_gc/GcManager.h"

#include "instance/instance_exception/NullPointerExceptionClassDeclare.h"
#include "instance/instance_exception/ExceptionInterrupt.h"
#include "instance/instance_exception/ArrayOutOfBoundsExceptionClassDeclare.h"
#include "instance/instance_exception/TypeCastExceptionClassDeclare.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_dom/DomArrayVariable.h"
#include "instance/instance_dom/DomRuntimeReference.h"


namespace alinous {

ArrayReferenceAccess::ArrayReferenceAccess(ArrayReferenceExpression* arrayRefExp)
				: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_ARRAY_REF){
	this->arrayRefExp = arrayRefExp;
	this->expAccess = nullptr;
	this->atype = nullptr;
}

ArrayReferenceAccess::~ArrayReferenceAccess() {
	delete this->expAccess;
	delete this->atype;
}

void ArrayReferenceAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	this->expAccess->analyze(actx, lastIinst, element);

	AnalyzedType at = this->expAccess->getAnalyzedType();
	int dim = this->arrayRefExp->getDim();
	int previousDim = at.getDim();
	dim = previousDim - dim;

	if(at.getType() == AnalyzedType::TYPE_DOM || at.getType() == AnalyzedType::TYPE_DOM_VALUE){
		analyzeDomArray(actx, lastIinst, element);
		return;
	}

	if(dim < 0){
		actx->addValidationError(ValidationError::CODE_ARRAY_INDEX_OVERFLOW, element, L"Array dimension is too greater than the variable.", {});
		this->atype = new AnalyzedType();
		return;
	}

	at.setDim(dim);
	this->atype = new AnalyzedType(at);

	analyzeDimensions(actx, lastIinst, element);
}

void ArrayReferenceAccess::analyzeDimensions(AnalyzeContext* actx,	AbstractVariableInstraction* lastIinst, CodeElement* element) {
	const ArrayList<AbstractExpression>* list = this->arrayRefExp->getIndexList();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* ex = list->get(i);
		ex->analyze(actx);

		AnalyzedType at = ex->getType(actx);
		bool res = VmArrayInstanceUtils::isArrayIndex(at);
		if(!res){
			actx->addValidationError(ValidationError::CODE_ARRAY_INDEX_MUST_BE_NUMERIC, element, L"Array index must be numeric value.", {});
		}
	}
}

void ArrayReferenceAccess::analyzeDomArray(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	this->atype = new AnalyzedType(AnalyzedType::TYPE_DOM_VALUE);
}

AnalyzedType ArrayReferenceAccess::getAnalyzedType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* ArrayReferenceAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->expAccess->interpret(vm ,lastInst);
	if(inst == nullptr || inst->isNull()){
		NullPointerExceptionClassDeclare::throwException(vm, getCodeElement());
		ExceptionInterrupt::interruptPoint(vm);
	}
	releaser.registerInstance(inst);

	uint8_t t = this->atype->getType();
	if(t == AnalyzedType::TYPE_DOM || t == AnalyzedType::TYPE_DOM_VALUE){
		return interpretDomArray(vm, lastInst, inst);
	}

	IAbstractVmInstanceSubstance* sub = inst->getInstance();
	VmArrayInstance* arrayInst = dynamic_cast<VmArrayInstance*>(sub);

	const ArrayList<AbstractExpression>* list = this->arrayRefExp->getIndexList();

	int maxLoop = list->size() - 1;
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* indexExp = list->get(i);

		AbstractVmInstance* index = indexExp->interpret(vm);
		releaser.registerInstance(index);

		PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(index);
		int idx = ref->getIntValue();

		if(idx >= arrayInst->size()){
			ArrayOutOfBoundsExceptionClassDeclare::throwException(vm, getCodeElement());
			ExceptionInterrupt::interruptPoint(vm);
		}

		AbstractReference* element = arrayInst->getReference(vm, idx);
		sub = element->getInstance();
		arrayInst = dynamic_cast<VmArrayInstance*>(sub);
	}


	AbstractExpression* indexExp = list->get(maxLoop);
	AbstractVmInstance* index = indexExp->interpret(vm);
	releaser.registerInstance(index);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(index);
	int idx = ref->getIntValue();

	if(idx >= arrayInst->size()){
		ArrayOutOfBoundsExceptionClassDeclare::throwException(vm, getCodeElement());
		ExceptionInterrupt::interruptPoint(vm);
	}

	AbstractReference* element = arrayInst->getReference(vm, idx);

	return element;
}

AbstractVmInstance* ArrayReferenceAccess::interpretDomArray(VirtualMachine* vm, AbstractVmInstance* lastInst, AbstractVmInstance* inst) {
	IAbstractVmInstanceSubstance* sub = inst->getInstance();
	DomArrayVariable* domArray = dynamic_cast<DomArrayVariable*>(sub);
	if(domArray == nullptr){
		TypeCastExceptionClassDeclare::throwException(vm, this->arrayRefExp);
		ExceptionInterrupt::interruptPoint(vm);
	}

	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	const ArrayList<AbstractExpression>* list = this->arrayRefExp->getIndexList();

	int maxLoop = list->size() - 1;
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* indexExp = list->get(i);

		AbstractVmInstance* index = indexExp->interpret(vm);
		releaser.registerInstance(index);

		PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(index);
		int idx = ref->getIntValue();

		if(idx >= domArray->size()){
			ArrayOutOfBoundsExceptionClassDeclare::throwException(vm, this->arrayRefExp);
			ExceptionInterrupt::interruptPoint(vm);
		}

		DomRuntimeReference* rr = domArray->get(idx);
		if(rr->isNull()){
			NullPointerExceptionClassDeclare::throwException(vm, this->arrayRefExp);
			ExceptionInterrupt::interruptPoint(vm);
		}

		IAbstractVmInstanceSubstance* elementInst = rr->getInstance();
		domArray = dynamic_cast<DomArrayVariable*>(elementInst);

		if(domArray == nullptr){
			TypeCastExceptionClassDeclare::throwException(vm, this->arrayRefExp);
			ExceptionInterrupt::interruptPoint(vm);
		}
	}

	AbstractExpression* indexExp = list->get(maxLoop);
	AbstractVmInstance* index = indexExp->interpret(vm);
	releaser.registerInstance(index);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(index);
	int idx = ref->getIntValue();

	if(idx >= domArray->size()){
		ArrayOutOfBoundsExceptionClassDeclare::throwException(vm, this->arrayRefExp);
		ExceptionInterrupt::interruptPoint(vm);
	}

	DomRuntimeReference* rr = domArray->get(idx);

	return rr;
}


CodeElement* ArrayReferenceAccess::getCodeElement() const noexcept {
	return this->arrayRefExp;
}

void ArrayReferenceAccess::setExpressionAccess(AbstractVariableInstraction* expAccess) noexcept {
	this->expAccess = expAccess;
}

} /* namespace alinous */
