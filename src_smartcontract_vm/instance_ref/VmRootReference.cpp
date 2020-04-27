/*
 * VmRootReference.cpp
 *
 *  Created on: 2019/07/08
 *      Author: iizuka
 */

#include "instance_ref/VmRootReference.h"
#include "instance_gc/GcManager.h"
#include "instance_ref_static/StaticInstanceHolder.h"

#include "vm/VirtualMachine.h"

#include "instance_ref/RefereceFactory.h"
#include "instance/VmClassInstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_ref_class_static/StaticClassReferenceHolder.h"


namespace alinous {

VmRootReference::VmRootReference(VirtualMachine* vm) : AbstractReference(this, VmInstanceTypesConst::REF_ROOT) {
	this->vm = vm;
	this->mainInst = nullptr;
	this->staticHolder = new StaticInstanceHolder();
	this->classStaticHolder = new StaticClassReferenceHolder();
}

VmRootReference::~VmRootReference() {
	clearInnerReferences();

	delete this->staticHolder;
	delete this->classStaticHolder;
}

void VmRootReference::clearInnerReferences() {
	if(this->mainInst != nullptr){
		GcManager* gc = this->vm->getGc();

		gc->removeObject(this);
		this->mainInst = nullptr;

		this->staticHolder->removeInnerReferences(this, this->vm);
		this->staticHolder->removeStringConst(this, this->vm);

		this->classStaticHolder->removeInnerReferences(this, this->vm);

		this->mainInst = nullptr;
	}
}

void VmRootReference::setMainInstance(VmClassInstance* mainInst) noexcept {
	this->mainInst = mainInst;

	GcManager* gc = this->vm->getGc();
	gc->registerObject(this);
}


IAbstractVmInstanceSubstance* VmRootReference::getInstance() noexcept {
	return this->mainInst;
}


PrimitiveReference* VmRootReference::newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm) {
	return this->staticHolder->newNumericConstReferenece(value, type ,vm);
}

VmStringInstance* VmRootReference::newStringConstReferenece(VmRootReference* rootRef, const UnicodeString* str, VirtualMachine* vm) {
	return this->staticHolder->newStringConstInstance(rootRef, str, vm);
}

AbstractReference* VmRootReference::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {
	return nullptr;
}

uint8_t VmRootReference::getInstType() const noexcept {
	return getType();
}

const VMemList<AbstractReference>* VmRootReference::getInstReferences() const noexcept {
	return getReferences();
}

int VmRootReference::instHashCode() const noexcept {
	return hashCode();
}

bool VmRootReference::instIsNull() const noexcept {
	return isNull();
}

int VmRootReference::instValueCompare(IAbstractVmInstanceSubstance* right) {
	return valueCompare(right);
}

AbstractExtObject* VmRootReference::instToClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return toClassExtObject(name, table);
}

bool VmRootReference::instIsPrimitive() const noexcept {
	return isPrimitive();
}

AnalyzedType VmRootReference::getRuntimeType() const noexcept {
	return AnalyzedType();
}

int VmRootReference::valueCompare(IAbstractVmInstanceSubstance* right) {
	return 0;
}

StaticClassReferenceHolder* VmRootReference::getStaticClassReferenceHolder() const noexcept {
	return this->classStaticHolder;
}

} /* namespace alinous */
