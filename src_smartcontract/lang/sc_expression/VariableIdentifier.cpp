/*
 * VariableIdentifier.cpp
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#include "lang/sc_expression/VariableIdentifier.h"
#include "base/UnicodeString.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "engine/sc_analyze_stack/AnalyzeStackManager.h"

#include "vm/variable_access/AbstractVariableInstraction.h"
#include "vm/variable_access/StackVariableAccess.h"
#include "vm/variable_access/MemberVariableAccess.h"
#include "vm/variable_access/ThisPointerAccess.h"

#include "instance/instance_ref/AbstractReference.h"

#include "engine/sc_analyze/AnalyzedClass.h"
#include "engine/sc_analyze/ValidationError.h"

#include "engine/sc_analyze_functions/VTableRegistory.h"
#include "engine/sc_analyze_functions/VTableClassEntry.h"

#include "engine/sc_analyze_variables/MemberVariableTable.h"

#include "instance/instance_ref_class_static_meta/StaticVariableMetadata.h"
#include "instance/instance_ref_class_static_meta/StaticClassMetadataHolder.h"
#include "instance/instance_ref_class_static/StaticClassEntry.h"
#include "instance/instance_ref_class_static_meta/StaticClassMetadata.h"


namespace alinous {

const UnicodeString VariableIdentifier::__THIS(L"this");
const UnicodeString VariableIdentifier::__SUPER(L"super");

VariableIdentifier::VariableIdentifier() : AbstractExpression(CodeElement::EXP_VARIABLE_ID) {
	this->name = nullptr;
	this->thisAccess = nullptr;
	this->access = nullptr;
	this->executable = false;
	this->staticMetadata = nullptr;
}

VariableIdentifier::~VariableIdentifier() {
	delete this->name;
	delete this->thisAccess;
	delete this->access;
	this->staticMetadata = nullptr;
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
	memAccess->analyze(actx, this->thisAccess, nullptr);

	if(memAccess->hasErrorOnAnalyze()){
		delete this->access;
		delete this->thisAccess;

		this->access = nullptr;
		this->thisAccess = nullptr;

		// static access
		StaticClassMetadataHolder* staticMetaHolder = actx->getStaticVariableHolder();
		AnalyzedClass* thisClazz = actx->getThisClass();
		const UnicodeString* fqn = thisClazz->getFullQualifiedName();

		this->staticMetadata = staticMetaHolder->findVariableMetadata(fqn, this->name);
		if(this->staticMetadata == nullptr){
			actx->addValidationError(ValidationError::CODE_CLASS_MEMBER_AND_STACK_VARIABLE_DO_NOT_EXISTS, this, L"Variable for the identifier '{0}' does not exists.", {this->name});
		}
	}
}

void VariableIdentifier::setName(UnicodeString* name) noexcept {
	this->name = name;
}

const UnicodeString* VariableIdentifier::getName() const noexcept {
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
	if(this->access != nullptr){
		return this->access->getAnalyzedType();
	}
	else if(this->staticMetadata != nullptr){
		return this->staticMetadata->getAnalyzedType();
	}

	return AnalyzedType();
}

void VariableIdentifier::init(VirtualMachine* vm) {
}

AbstractVmInstance* VariableIdentifier::interpret(VirtualMachine* vm) {
	AbstractVmInstance* lastInst = nullptr;

	if(this->thisAccess != nullptr){
		lastInst = this->thisAccess->interpret(vm, nullptr);
	}
	else if(this->staticMetadata != nullptr){
		int index = this->staticMetadata->getIndex();
		StaticClassMetadata* classMeta = this->staticMetadata->getParent();
		StaticClassEntry* entry = classMeta->getStaticClassEntry();

		AbstractReference* ref = entry->getReferenceByIndex(index);

		return ref;
	}

	AbstractVmInstance* instOrRef = this->access->interpret(vm, lastInst);

	return instOrRef;
}

bool VariableIdentifier::isThis() const noexcept {
	return __THIS.equals(this->name);
}

bool VariableIdentifier::isSuper() const noexcept {
	return __SUPER.equals(this->name);
}

} /* namespace alinous */
