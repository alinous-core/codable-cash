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


namespace alinous {

MemberVariableAccess::MemberVariableAccess(VariableIdentifier* valId) {
	this->valId = valId;
	this->memberIndex = -1;
	this->atype = nullptr;
}

MemberVariableAccess::~MemberVariableAccess() {
	delete this->atype;
}

void MemberVariableAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
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
	}
}

AnalyzedType MemberVariableAccess::getAnalyzedType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* MemberVariableAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	VmClassInstance* clazzInst = dynamic_cast<VmClassInstance*>(lastInst);

	const VMemList<AbstractReference>* list = clazzInst->getReferences();
	AbstractReference* ref = list->get(this->memberIndex);

	return ref;
}

bool MemberVariableAccess::hasErrorOnAnalyze() const noexcept {
	return this->memberIndex < 0;
}

CodeElement* MemberVariableAccess::getCodeElement() const noexcept {
	return this->valId;
}

} /* namespace alinous */
