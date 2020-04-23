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
#include "sc_analyze/IVmInstanceFactory.h"
#include "sc_analyze/AnalyzedType.h"

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

#include "instance_exception/ExceptionInterrupt.h"

namespace alinous {

VmClassInstance::VmClassInstance(AnalyzedClass* clazz, VirtualMachine* vm) :
		AbstractVmInstance(VmInstanceTypesConst::INST_OBJ), clazz(clazz), members(vm) {

}

VmClassInstance::VmClassInstance(uint8_t type, AnalyzedClass* clazz, VirtualMachine* vm) :
		AbstractVmInstance(type), clazz(clazz), members(vm) {
}

VmClassInstance::~VmClassInstance() {
	int maxLoop = this->members.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->members.get(i);

		delete ref;
	}
}

VmClassInstance* VmClassInstance::createObject(AnalyzedClass* clazz, VirtualMachine* vm) {
	IVmInstanceFactory* factory = findFactory(clazz);
	VmClassInstance* inst = nullptr;
	if(factory != nullptr){
		inst = factory->createInstance(clazz, vm);
	}
	else{
		inst = new(vm) VmClassInstance(clazz, vm);
	}

	try{
		inst->init(vm);
	}
	catch(ExceptionInterrupt* e){
		GcManager* gc = vm->getGc();
		gc->handleFloatingObject(inst);

		throw e;
	}
	return inst;
}

IVmInstanceFactory* VmClassInstance::findFactory(AnalyzedClass* clazz) noexcept {
	while(clazz != nullptr){
		IVmInstanceFactory* factory = clazz->getFactory();
		if(factory != nullptr){
			return factory;
		}

		clazz = clazz->getExtends();
	}

	return nullptr;
}

void VmClassInstance::removeInnerRefs(GcManager* gc) noexcept {
	int maxLoop = this->members.size();

	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->members.get(i);

		// remove ref
		gc->removeObject(ref);
	}
}

int VmClassInstance::valueCompare(IAbstractVmInstanceSubstance* right) {
	VmClassInstance* rightPtr = dynamic_cast<VmClassInstance*>(right);

	int64_t diff = (int64_t)((void*)this) - (int64_t)((void*)rightPtr);
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

bool VmClassInstance::instIsPrimitive() const noexcept {
	return false;
}

void VmClassInstance::init(VirtualMachine* vm) {
	ArrayList<MemberVariableDeclare>* list = this->clazz->getMemberVariableDeclareList();
	GcManager* gc = vm->getGc();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* dec = list->get(i);

		AbstractReference* ref = RefereceFactory::createReferenceFromDefinition(this, dec, vm);
		ref->setOwner(this);
		this->members.addElement(ref);

		gc->registerObject(ref);
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

AnalyzedType VmClassInstance::getRuntimeType() const noexcept {
	return AnalyzedType(this->clazz);
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
