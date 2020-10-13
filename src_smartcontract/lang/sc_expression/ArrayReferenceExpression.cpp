/*
 * ArrayReferenceExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression/ArrayReferenceExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/ValidationError.h"

#include "instance/instance_array/VmArrayInstanceUtils.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"
#include "instance/instance_gc/GcManager.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_exception/NullPointerExceptionClassDeclare.h"
#include "instance/instance_exception/ExceptionInterrupt.h"
#include "instance/instance_exception/ArrayOutOfBoundsExceptionClassDeclare.h"
#include "instance/instance_exception/TypeCastExceptionClassDeclare.h"

#include "instance/instance_dom/DomArrayVariable.h"
#include "instance/instance_dom/DomRuntimeReference.h"

#include "instance/IAbstractVmInstanceSubstance.h"


namespace alinous {

ArrayReferenceExpression::ArrayReferenceExpression() : AbstractExpression(CodeElement::EXP_ARRAY_REF) {
	this->exp = nullptr;
	this->atype = nullptr;
}

ArrayReferenceExpression::~ArrayReferenceExpression() {
	delete this->exp;
	this->list.deleteElements();

	delete this->atype;
}

void ArrayReferenceExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* ex = this->list.get(i);
		ex->setParent(this);
		ex->preAnalyze(actx);
	}

	setThrowsException(true);
}

void ArrayReferenceExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* ex = this->list.get(i);
		ex->analyzeTypeRef(actx);
	}
}

void ArrayReferenceExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* ex = this->list.get(i);
		ex->analyze(actx);

		AnalyzedType at = ex->getType(actx);
		bool res = VmArrayInstanceUtils::isArrayIndex(at);
		if(!res){
			actx->addValidationError(ValidationError::CODE_ARRAY_INDEX_MUST_BE_NUMERIC, this, L"Array index must be numeric value.", {});
		}
	}

	if(actx->hasError()){
		this->atype = new AnalyzedType();
		return;
	}

	AnalyzedType at = this->exp->getType(actx);
	if(at.getType() == AnalyzedType::TYPE_DOM || at.getType() == AnalyzedType::TYPE_DOM_VALUE){
		analyzeDomArray(actx);
		return;
	}

	int dim = at.getDim();
	int reqDim = this->list.size();
	if(dim < reqDim){
		actx->addValidationError(ValidationError::CODE_ARRAY_INDEX_OVERFLOW, this, L"Array dimension is too greater than the variable.", {});
		return;
	}

	at.setDim(dim - reqDim);
	this->atype = new AnalyzedType(at);
}

void ArrayReferenceExpression::analyzeDomArray(AnalyzeContext* actx) {
	this->atype = new AnalyzedType(AnalyzedType::TYPE_DOM_VALUE);
}

void ArrayReferenceExpression::setExp(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

AbstractExpression* ArrayReferenceExpression::getExp() const noexcept {
	return this->exp;
}


void ArrayReferenceExpression::addIndex(AbstractExpression* exp) noexcept {
	this->list.addElement(exp);
}

int ArrayReferenceExpression::getDim() const noexcept {
	return this->list.size();
}

const ArrayList<AbstractExpression>* ArrayReferenceExpression::getIndexList() const noexcept {
	return &this->list;
}

int ArrayReferenceExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	total+= sizeof(uint32_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* ex = this->list.get(i);
		total += ex->binarySize();
	}

	return total;
}

void ArrayReferenceExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);
	out->putShort(CodeElement::EXP_ARRAY_REF);

	this->exp->toBinary(out);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* ex = this->list.get(i);
		ex->toBinary(out);
	}
}

void ArrayReferenceExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		element = createFromBinary(in);
		checkIsExp(element);

		AbstractExpression* ex = dynamic_cast<AbstractExpression*>(element);
		this->list.addElement(ex);
	}
}

AnalyzedType ArrayReferenceExpression::getType(AnalyzeContext* actx) {
	return *this->atype;
}

void ArrayReferenceExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* ex = this->list.get(i);
		ex->init(vm);
	}
}

AbstractVmInstance* ArrayReferenceExpression::interpret(VirtualMachine* vm) {
	AbstractVmInstance* inst = this->exp->interpret(vm);
	if(inst == nullptr || inst->isNull()){
		NullPointerExceptionClassDeclare::throwException(vm, this);
		ExceptionInterrupt::interruptPoint(vm);
	}

	if(this->atype->getType() == AnalyzedType::TYPE_DOM_VALUE){
		return interpretDomArray(vm, inst);
	}

	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	releaser.registerInstance(inst);
	IAbstractVmInstanceSubstance* sub = inst->getInstance();
	VmArrayInstance* arrayInst = dynamic_cast<VmArrayInstance*>(sub);

	int maxLoop = this->list.size() - 1;
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* indexExp = this->list.get(i);

		AbstractVmInstance* index = indexExp->interpret(vm);
		releaser.registerInstance(index);

		PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(index);
		int idx = ref->getIntValue();

		if(idx >= arrayInst->size()){
			ArrayOutOfBoundsExceptionClassDeclare::throwException(vm, this);
			ExceptionInterrupt::interruptPoint(vm);
		}

		AbstractReference* element = arrayInst->getReference(vm, idx);
		sub = element->getInstance();
		arrayInst = dynamic_cast<VmArrayInstance*>(sub);
	}

	AbstractExpression* indexExp = this->list.get(maxLoop);
	AbstractVmInstance* index = indexExp->interpret(vm);
	releaser.registerInstance(index);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(index);
	int idx = ref->getIntValue();

	if(idx >= arrayInst->size()){
		ArrayOutOfBoundsExceptionClassDeclare::throwException(vm, this);
		ExceptionInterrupt::interruptPoint(vm);
	}

	AbstractReference* element = arrayInst->getReference(vm, idx);

	return element;
}

AbstractVmInstance* ArrayReferenceExpression::interpretDomArray(VirtualMachine* vm, AbstractVmInstance* inst) {
	IAbstractVmInstanceSubstance* sub = inst->getInstance();
	DomArrayVariable* domArray = dynamic_cast<DomArrayVariable*>(sub);
	if(domArray == nullptr){
		TypeCastExceptionClassDeclare::throwException(vm, this);
		ExceptionInterrupt::interruptPoint(vm);
	}

	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	int maxLoop = this->list.size() - 1;
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* indexExp = this->list.get(i);

		AbstractVmInstance* index = indexExp->interpret(vm);
		releaser.registerInstance(index);

		PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(index);
		int idx = ref->getIntValue();

		if(idx >= domArray->size()){
			ArrayOutOfBoundsExceptionClassDeclare::throwException(vm, this);
			ExceptionInterrupt::interruptPoint(vm);
		}

		DomRuntimeReference* rr = domArray->get(idx);
		if(rr->isNull()){
			NullPointerExceptionClassDeclare::throwException(vm, this);
			ExceptionInterrupt::interruptPoint(vm);
		}

		IAbstractVmInstanceSubstance* elementInst = rr->getInstance();
		domArray = dynamic_cast<DomArrayVariable*>(elementInst);

		if(domArray == nullptr){
			TypeCastExceptionClassDeclare::throwException(vm, this);
			ExceptionInterrupt::interruptPoint(vm);
		}
	}

	AbstractExpression* indexExp = this->list.get(maxLoop);
	AbstractVmInstance* index = indexExp->interpret(vm);
	releaser.registerInstance(index);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(index);
	int idx = ref->getIntValue();

	if(idx >= domArray->size()){
		ArrayOutOfBoundsExceptionClassDeclare::throwException(vm, this);
		ExceptionInterrupt::interruptPoint(vm);
	}

	DomRuntimeReference* rr = domArray->get(idx);

	return rr;
}

} /* namespace alinous */
