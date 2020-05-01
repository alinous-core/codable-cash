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

	TypeResolver* typeResolver = actx->getTypeResolver();

	AnalyzedType atype = lastIinst->getAnalyzedType();
	AnalyzedClass* clazz = atype.getAnalyzedClass();

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
	if(lastInst == nullptr || lastInst->isNull()){
		NullPointerExceptionClassDeclare::throwException(vm, this->element);
		ExceptionInterrupt::interruptPoint(vm);
	}

	VmClassInstance* clazzInst = dynamic_cast<VmClassInstance*>(lastInst->getInstance());

	const VMemList<AbstractReference>* list = clazzInst->getReferences();
	AbstractReference* ref = list->get(this->memberIndex);

	return ref;
}

bool MemberVariableAccess::hasErrorOnAnalyze() const noexcept {
	return this->memberIndex < 0 && this->meta == nullptr;
}

CodeElement* MemberVariableAccess::getCodeElement() const noexcept {
	return this->valId;
}

} /* namespace alinous */
