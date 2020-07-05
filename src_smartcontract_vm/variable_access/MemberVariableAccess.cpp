/*
 * MemberVariableAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/MemberVariableAccess.h"

#include "sc_expression/VariableIdentifier.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/ValidationError.h"

#include "sc_declare/MemberVariableDeclare.h"

#include "base/UnicodeString.h"

#include "instance/VmClassInstance.h"
#include "instance_ref/AbstractReference.h"
#include "instance_parts/VMemList.h"

#include "instance_exception/NullPointerExceptionClassDeclare.h"
#include "instance_exception/ExceptionInterrupt.h"

#include "variable_access/AbstractVariableInstraction.h"
#include "variable_access/ClassTypeAccess.h"

#include "instance_ref_class_static_meta/StaticClassMetadataHolder.h"
#include "instance_ref_class_static_meta/StaticVariableMetadata.h"
#include "instance_ref_class_static_meta/StaticClassMetadata.h"

#include "instance_ref_class_static/StaticClassEntry.h"

#include "instance_dom/DomVariableInstance.h"

#include "instance_string/VmStringInstance.h"

#include "instance_gc/StackFloatingVariableHandler.h"

#include "instance_dom/DomRuntimeReference.h"

namespace alinous {

MemberVariableAccess::MemberVariableAccess(VariableIdentifier* valId)
				: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_MEMBER_VARIABLE) {
	this->valId = valId;
	this->memberIndex = -1;
	this->atype = nullptr;
	this->element = nullptr;
	this->meta = nullptr;
}

MemberVariableAccess::~MemberVariableAccess() {
	delete this->atype;
}

void MemberVariableAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	this->element = element;

	uint8_t instType = lastIinst->getType();
	if(instType == AbstractVariableInstraction::INSTRUCTION_CLASS_TYPE){
		analyzeStaticWithClassType(actx, lastIinst);
		return;
	}

	AnalyzedType atype = lastIinst->getAnalyzedType();
	if(atype.getType() == AnalyzedType::TYPE_DOM){
		analyzeDomType(actx, lastIinst);
		return;
	}

	AnalyzedClass* clazz = atype.getAnalyzedClass();

	TypeResolver* typeResolver = actx->getTypeResolver();
	const UnicodeString* name = this->valId->getName();

	ArrayList<MemberVariableDeclare>* list = clazz->getMemberVariableDeclareList();
	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* dec = list->get(i);
		const UnicodeString* memberName = dec->getName();

		if(memberName->equals(name)){
			this->memberIndex = i;
			this->atype = typeResolver->resolveType(dec, dec->getType());
			break;
		}
	}

	// error
	if(element != nullptr && this->memberIndex < 0){
		actx->addValidationError(ValidationError::CODE_CLASS_MEMBER_DOES_NOT_EXISTS, this->valId, L"The variable '{0}' does not exists.", {name});
		this->hasError = true;
	}
}


void MemberVariableAccess::analyzeDomType(AnalyzeContext* actx,	AbstractVariableInstraction* lastIinst) {
	this->atype = new AnalyzedType(AnalyzedType::TYPE_DOM_VALUE);
}

void MemberVariableAccess::analyzeStaticWithClassType(AnalyzeContext* actx,	AbstractVariableInstraction* lastIinst) {
	ClassTypeAccess* classType = dynamic_cast<ClassTypeAccess*>(lastIinst);
	const UnicodeString* name = this->valId->getName();

	AnalyzedType at = classType->getAnalyzedType();
	AnalyzedClass* clazz = at.getAnalyzedClass();

	// index and atype
	StaticClassMetadataHolder* staticHolder = actx->getStaticVariableHolder();

	const UnicodeString* fqn = clazz->getFullQualifiedName();
	this->meta = staticHolder->findVariableMetadata(fqn, name);
	if(meta == nullptr){
		actx->addValidationError(ValidationError::CODE_CLASS_MEMBER_DOES_NOT_EXISTS, this->valId, L"The variable '{0}' does not exists.", {name});
		this->hasError = true;
		this->atype = new AnalyzedType();

		return;
	}

	AnalyzedType metaAt = this->meta->getAnalyzedType();
	this->atype = new AnalyzedType(metaAt);
}

AnalyzedType MemberVariableAccess::getAnalyzedType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* MemberVariableAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	if(this->meta != nullptr){
		return interpretStaticWithClassType(vm, lastInst);
	}

	if(lastInst == nullptr || lastInst->isNull()){
		NullPointerExceptionClassDeclare::throwException(vm, this->element);
		ExceptionInterrupt::interruptPoint(vm);
	}

	if(this->atype != nullptr && this->atype->getType() == AnalyzedType::TYPE_DOM_VALUE){
		return interpretDomType(vm, lastInst);
	}

	VmClassInstance* clazzInst = dynamic_cast<VmClassInstance*>(lastInst->getInstance());

	const VMemList<AbstractReference>* list = clazzInst->getReferences();
	AbstractReference* ref = list->get(this->memberIndex);

	return ref;
}

AbstractVmInstance* MemberVariableAccess::interpretDomType(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	IAbstractVmInstanceSubstance* inst = lastInst->getInstance();
	DomVariableInstance* dom = dynamic_cast<DomVariableInstance*>(inst);

	assert(dom != nullptr);

	const UnicodeString* name = this->valId->getName();
	VmStringInstance* key = new(vm) VmStringInstance(vm, name);
	releaser.registerInstance(key);

	DomRuntimeReference* rr = dom->getProperty(vm, key);
	if(lastInst == nullptr){
		NullPointerExceptionClassDeclare::throwException(vm, this->element);
		ExceptionInterrupt::interruptPoint(vm);
	}

	return rr;
}

bool MemberVariableAccess::hasErrorOnAnalyze() const noexcept {
	if(this->atype != nullptr && this->atype->getType() == AnalyzedType::TYPE_DOM_VALUE){
		return false;
	}

	return this->memberIndex < 0 && this->meta == nullptr;
}

CodeElement* MemberVariableAccess::getCodeElement() const noexcept {
	return this->valId;
}

AbstractVmInstance* MemberVariableAccess::interpretStaticWithClassType(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	int index = this->meta->getIndex();
	StaticClassMetadata* classMeta = this->meta->getParent();
	StaticClassEntry* entry = classMeta->getStaticClassEntry();

	AbstractReference* ref = entry->getReferenceByIndex(index);

	return ref;
}

} /* namespace alinous */
