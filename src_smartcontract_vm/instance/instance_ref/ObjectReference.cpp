/*
 * ObjectReference.cpp
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#include "instance/instance_ref/ObjectReference.h"

#include "instance/VmClassInstance.h"
#include "instance/VmInstanceTypesConst.h"
#include "instance/instance_gc/GcManager.h"

#include "instance/instance_string/VmStringInstance.h"

#include "ext_binary/ExtStringClass.h"
#include "ext_binary/ExtNullPtrObject.h"

#include "instance/AbstractVmInstance.h"
namespace alinous {

ObjectReference::ObjectReference(IAbstractVmInstanceSubstance* owner, uint8_t type, uint8_t instanceType) : AbstractReference(owner, type) {
	this->instance = nullptr;
	this->instanceType = instanceType;
}

ObjectReference::~ObjectReference() {

}

ObjectReference* ObjectReference::createObjectReference(IAbstractVmInstanceSubstance* owner, VmClassInstance* clazzInst, VirtualMachine* vm) {
	ObjectReference* ref = new(vm) ObjectReference(owner, VmInstanceTypesConst::REF_OBJ, ObjectReference::CLASS_INSTANCE);
	ref->setInstance(clazzInst);

	return ref;
}

ObjectReference* ObjectReference::createStringReference(IAbstractVmInstanceSubstance* owner, VmStringInstance* clazzInst, VirtualMachine* vm) {
	ObjectReference* ref = new(vm) ObjectReference(owner, VmInstanceTypesConst::REF_OBJ, ObjectReference::STRING_INSTANCE);
	ref->setInstance(clazzInst);

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

const UnicodeString* ObjectReference::toString() const noexcept {
	AbstractVmInstance* inst = dynamic_cast<AbstractVmInstance*>(this->instance);

	return (isNull() || inst == nullptr) ? AbstractReference::toString() : inst->toString();
}

void ObjectReference::resetOnGc() noexcept {
	this->instance = nullptr;
}

AbstractExtObject* ObjectReference::createNullObject(const UnicodeString* name, VTableRegistory* table) {
	//if(this->instanceType == ObjectReference::STRING_INSTANCE){
	//	return new ExtStringClass(name);
	//}

	uint8_t type = this->instanceType == ObjectReference::STRING_INSTANCE ? VmInstanceTypesConst::INST_STRING : VmInstanceTypesConst::INST_OBJ;

	return new ExtNullPtrObject(name, type);
}

bool ObjectReference::isNull() const noexcept {
	return this->instance == nullptr;
}

int ObjectReference::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	if(isNull()){
		return right == nullptr ? 0 : -1;
	}
	else if(right == nullptr){
		return isNull() ? 0 : 1;
	}

	return this->instance->instValueCompare(right);
}

} /* namespace alinous */
