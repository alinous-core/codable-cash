/*
 * VmArrayInstance.cpp
 *
 *  Created on: 2020/02/16
 *      Author: iizuka
 */

#include "instance/instance_array/VmArrayInstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "instance/instance_gc/GcManager.h"

#include "instance/instance_array/ArrayReference.h"

#include "ext_binary/ExtArrayObject.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "base/UnicodeString.h"

namespace alinous {

VmArrayInstance::VmArrayInstance(VirtualMachine* vm, int length, const AnalyzedType& atype) : AbstractVmInstance(VmInstanceTypesConst::INST_ARRAY) {
	this->array = new(vm) VMemList<AbstractReference>(vm);
	this->length = length;
	this->atype = new AnalyzedType(atype);

	for(int i = 0; i != length; ++i){
		this->array->addElement(nullptr);
	}

	this->str = nullptr;
}

VmArrayInstance::~VmArrayInstance() {
	int maxLoop = this->array->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->array->get(i);

		delete ref;
	}

	delete this->atype;
	delete this->array;
	delete this->str;
}

void VmArrayInstance::removeInnerRefs(GcManager* gc) noexcept {
	int maxLoop = this->array->size();

	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->array->get(i);

		if(ref == nullptr){
			continue;
		}

		// remove ref
		if(!ref->isPrimitive()){
			// ref->substitute(nullptr, gc);
			gc->removeObject(ref);
			ref->resetOnGc();
		}
	}
}

const VMemList<AbstractReference>* VmArrayInstance::getReferences() const noexcept {
	return this->array;
}

AbstractExtObject* VmArrayInstance::toClassExtObject(const UnicodeString* name,	VTableRegistory* reg) {
	ExtArrayObject* obj = new ExtArrayObject(name, this->length);

	int maxLoop = this->array->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->array->get(i);
		AbstractExtObject* innerObj = ref->toClassExtObject(name, reg);

		obj->addInnerElement(innerObj);
	}

	return obj;
}

int VmArrayInstance::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	const VmArrayInstance* inst = dynamic_cast<const VmArrayInstance*>(right);

	int64_t diff = ((int64_t)this) - ((int64_t)inst);
	if(diff == 0){
		return 0;
	}

	return diff > 0 ? 1 : -1;
}

IAbstractVmInstanceSubstance* VmArrayInstance::getInstance() noexcept {
	return this;
}

AbstractReference* VmArrayInstance::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {
	ArrayReference* ref = new(vm) ArrayReference(owner, vm, this);

	return ref;
}

uint8_t VmArrayInstance::getInstType() const noexcept {
	return getType();
}

const VMemList<AbstractReference>* VmArrayInstance::getInstReferences() const noexcept {
	return getReferences();
}

int VmArrayInstance::instHashCode() const noexcept {
	return hashCode();
}

bool VmArrayInstance::instIsNull() const noexcept {
	return isNull();
}

int VmArrayInstance::instValueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	return valueCompare(right);
}

AbstractExtObject* VmArrayInstance::instToClassExtObject(
		const UnicodeString* name, VTableRegistory* table) {
	return toClassExtObject(name, table);
}

bool VmArrayInstance::instIsPrimitive() const noexcept {
	return false;
}

void VmArrayInstance::setReference(VirtualMachine* vm, int pos, AbstractReference* ref) noexcept {
	GcManager* gc = vm->getGc();

	AbstractReference* last = this->array->get(pos);
	if(last != nullptr){
		gc->removeObject(last);
	}

	if(ref != nullptr){
		gc->registerObject(ref);
		this->array->setElement(ref, pos);

		if(ref->isPrimitive()){
			ref->setOwner(this);
		}
	}
	else{
		this->array->setElement(nullptr, pos);
	}
}

AbstractReference* VmArrayInstance::getReference(VirtualMachine* vm, int pos) {
	return this->array->get(pos);
}

AnalyzedType VmArrayInstance::getRuntimeType() const noexcept {
	return *this->atype;
}

const UnicodeString* VmArrayInstance::toString() const noexcept {
	delete this->str;
	this->str = new UnicodeString(L"");

	int maxLoop = this->array->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->array->get(i);

		if(i > 0){
			this->str->append(L", ");
		}

		if(ref == nullptr){
			this->str->append(L"null");
		}
		else {
			const UnicodeString* s = ref->toString();
			this->str->append(s);
		}
	}

	return this->str;
}

int VmArrayInstance::size() const noexcept {
	return this->array->size();
}

} /* namespace alinous */
