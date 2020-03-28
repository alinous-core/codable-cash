/*
 * ObjectReference.cpp
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#include "instance_ref/ObjectReference.h"

#include "instance/VmClassInstance.h"
#include "instance/VmInstanceTypesConst.h"
#include "instance_gc/GcManager.h"

#include "instance_string/VmStringInstance.h"

#include "ext_binary/ExtStringClass.h"
namespace alinous {

ObjectReference::ObjectReference(IAbstractVmInstanceSubstance* owner, uint8_t type, uint8_t instanceType) : AbstractReference(owner, type) {
	this->instance = nullptr;
	this->instanceType = instanceType;
}

ObjectReference::~ObjectReference() {

}

ObjectReference* ObjectReference::createObjectReference(IAbstractVmInstanceSubstance* owner, VmClassInstance* clazzInst, VirtualMachine* vm, bool doGc) {
	ObjectReference* ref = new(vm) ObjectReference(owner, VmInstanceTypesConst::REF_OBJ, ObjectReference::CLASS_INSTANCE);
	ref->setInstance(clazzInst);

	if(doGc && clazzInst != nullptr){
		GcManager* gc = vm->getGc();
		gc->registerObject(ref);
	}

	return ref;
}

ObjectReference* ObjectReference::createObjectReference(IAbstractVmInstanceSubstance* owner, VmClassInstance* clazzInst, VirtualMachine* vm) {
	return createObjectReference(owner, clazzInst, vm, false);
}

ObjectReference* ObjectReference::createStringReference(IAbstractVmInstanceSubstance* owner, VmStringInstance* clazzInst, VirtualMachine* vm) {
	ObjectReference* ref = new(vm) ObjectReference(owner, VmInstanceTypesConst::REF_OBJ, ObjectReference::STRING_INSTANCE);
	ref->setInstance(clazzInst);

	if(clazzInst != nullptr){
		GcManager* gc = vm->getGc();
		gc->registerObject(ref);
	}

	return ref;
}

bool ObjectReference::isPrimitive() const noexcept {
	return false;
}

IAbstractVmInstanceSubstance* ObjectReference::getInstance() noexcept {
	return this->instance;
}

void ObjectReference::setInstance(IAbstractVmInstanceSubstance* instance) noexcept {
	this->instance = instance;
}

void ObjectReference::substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	if(this->instance != nullptr){
		gc->removeObject(this);
		this->instance = nullptr;
	}

	if(rightValue != nullptr && !rightValue->instIsNull()){
		this->instance = rightValue;
		gc->registerObject(this);
	}
	else {
		this->instance = nullptr;
	}
}

AbstractExtObject* ObjectReference::toClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	if(this->instance == nullptr){
		return createNullObject(name, table);
	}

	return this->instance->instToClassExtObject(name, table);
}

AbstractExtObject* ObjectReference::createNullObject(const UnicodeString* name, VTableRegistory* table) {
	//if(this->instanceType == ObjectReference::STRING_INSTANCE){
	//	return new ExtStringClass(name);
	//}

	return nullptr;
}

bool ObjectReference::isNull() const noexcept {
	return this->instance == nullptr;
}

int ObjectReference::valueCompare(IAbstractVmInstanceSubstance* right) {
	if(isNull()){
		return right == nullptr ? 0 : -1;
	}
	else if(right == nullptr){
		return isNull() ? 0 : 1;
	}

	return this->instance->instValueCompare(right);
}

} /* namespace alinous */
