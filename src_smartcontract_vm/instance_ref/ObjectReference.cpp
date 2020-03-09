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


namespace alinous {

ObjectReference::ObjectReference(uint8_t type) : AbstractReference(type) {
	this->instance = nullptr;
}

ObjectReference::~ObjectReference() {

}

ObjectReference* ObjectReference::createObjectReference(VmClassInstance* clazzInst, VirtualMachine* vm) {
	ObjectReference* ref = new(vm) ObjectReference(VmInstanceTypesConst::REF_OBJ);
	ref->setInstance(clazzInst);

	return ref;
}

bool ObjectReference::isPrimitive() const noexcept {
	return false;
}

AbstractVmInstance* ObjectReference::getInstance() noexcept {
	return this->instance;
}

void ObjectReference::setInstance(AbstractVmInstance* instance) noexcept {
	this->instance = instance;
}

void ObjectReference::substitute(AbstractVmInstance* rightValue, VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	if(this->instance != nullptr){
		gc->removeInstanceReference(this, this->instance);
		this->instance = nullptr;
	}

	if(!rightValue->isNull()){
		gc->addInstanceReference(this, rightValue);
		this->instance = rightValue;
	}
}

AbstractExtObject* ObjectReference::toClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return this->instance->toClassExtObject(name, table);
}

bool ObjectReference::isNull() const noexcept {
	return this->instance == nullptr;
}

int ObjectReference::valueCompare(const AbstractVmInstance* right) {
	if(isNull()){
		return right->isNull() ? 0 : -1;
	}
	else if(right->isNull()){
		return isNull() ? 0 : 1;
	}

	const ObjectReference* objRight = dynamic_cast<const ObjectReference*>(right);
	if(objRight == nullptr){
		return -1;
	}

	return this->instance->valueCompare(objRight->getInstance());
}

} /* namespace alinous */
