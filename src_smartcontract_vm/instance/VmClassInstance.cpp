/*
 * VmClassInstance.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "instance/VmClassInstance.h"
#include "instance_ref/AbstractReference.h"

#include "vm/VirtualMachine.h"

#include "sc_analyze/AnalyzedClass.h"
#include "sc_declare/MemberVariableDeclare.h"
#include "sc_analyze_functions/VTableRegistory.h"
#include "sc_analyze_functions/VTableClassEntry.h"

#include "sc_analyze_variables/MemberVariableTable.h"
#include "sc_analyze_variables/MemberVariableEntry.h"

#include "instance_ref/RefereceFactory.h"
#include "instance_gc/GcManager.h"

#include "instance/VmInstanceTypesConst.h"

#include "ext_binary/ExtClassObject.h"

#include "base/ArrayList.h"
#include "base/UnicodeString.h"

#include "instance_ref/ObjectReference.h"

namespace alinous {

VmClassInstance::VmClassInstance(AnalyzedClass* clazz, VirtualMachine* vm) :
		AbstractVmInstance(VmInstanceTypesConst::ISNT_OBJ), clazz(clazz), members(vm) {

}

VmClassInstance::~VmClassInstance() {
	int maxLoop = this->members.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->members.get(i);

		delete ref;
	}
}

VmClassInstance* VmClassInstance::createObject(AnalyzedClass* clazz, VirtualMachine* vm) {
	VmClassInstance* inst = new(vm) VmClassInstance(clazz, vm);
	inst->init(vm);

	return inst;
}

void VmClassInstance::removeInnerRefs(GcManager* gc) noexcept {
	int maxLoop = this->members.size();

	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->members.get(i);

		// remove ref
		gc->removeRefReference(this, ref);
	}
}

int VmClassInstance::valueCompare(IAbstractVmInstanceSubstance* right) {
	int64_t diff = (int64_t)this - (int64_t)right;
	if(diff == 0){
		return 0;
	}

	return diff > 0 ? 1 : -1;
}

IAbstractVmInstanceSubstance* VmClassInstance::getInstance() noexcept {
	return this;
}

AbstractReference* VmClassInstance::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {
	return ObjectReference::createObjectReference(owner, this, vm);
}

uint8_t VmClassInstance::getInstType() const noexcept {
	return getType();
}

const VMemList<AbstractReference>* VmClassInstance::getInstReferences() const noexcept {
	return getReferences();
}

int VmClassInstance::instHashCode() const noexcept {
	return hashCode();
}

bool VmClassInstance::instIsNull() const noexcept {
	return isNull();
}

int VmClassInstance::instValueCompare(IAbstractVmInstanceSubstance* right) {
	return valueCompare(right);
}

AbstractExtObject* VmClassInstance::instToClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return toClassExtObject(name, table);
}

void VmClassInstance::init(VirtualMachine* vm) {
	ArrayList<MemberVariableDeclare>* list = this->clazz->getMemberVariableDeclareList();
	GcManager* gc = vm->getGc();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* dec = list->get(i);

		AbstractReference* ref = RefereceFactory::createReferenceFromDefinition(dec, vm);
		this->members.addElement(ref);

		gc->addRefReference(this, ref);
	}

	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* dec = list->get(i);
		AbstractReference* ref = this->members.get(i);

		dec->onAllocate(vm, ref);
	}

}

const VMemList<AbstractReference>* VmClassInstance::getReferences() const noexcept {
	return &this->members;
}

AnalyzedClass* VmClassInstance::getAnalyzedClass() const noexcept {
	return this->clazz;
}

AbstractExtObject* VmClassInstance::toClassExtObject(const UnicodeString* name, VTableRegistory* reg) {
	ExtClassObject* extObj = new ExtClassObject(name);

	const UnicodeString* fqn = this->clazz->getFullQualifiedName();
	VTableClassEntry* classEntry = reg->getClassEntry(fqn, this->clazz);
	MemberVariableTable* table = classEntry->getMemberVariableTable();

	ArrayList<MemberVariableEntry>* list = table->getVariableList();

	int maxLoop = this->members.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->members.get(i);

		MemberVariableEntry* entry = list->get(i);
		const UnicodeString* variableName = entry->getName();

		AbstractExtObject* memberObj = ref->toClassExtObject(variableName, reg);
		extObj->add(memberObj);
	}

	return extObj;
}

} /* namespace alinous */
