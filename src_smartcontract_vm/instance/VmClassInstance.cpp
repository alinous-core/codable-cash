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

#include "base/ArrayList.h"

#include "instance_ref/RefereceFactory.h"
#include "instance_gc/GcManager.h"

namespace alinous {

VmClassInstance::VmClassInstance(AnalyzedClass* clazz, VirtualMachine* vm) :
		AbstractVmInstance(AbstractVmInstance::ISNT_OBJ), clazz(clazz), members(vm) {

}

VmClassInstance::~VmClassInstance() {
	int maxLoop = this->members.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->members.get(i);
		if(!ref->isPrimitive()) delete ref;
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

}

const VMemList<AbstractReference>* VmClassInstance::getReferences() const noexcept {
	return &this->members;
}

AnalyzedClass* VmClassInstance::getAnalyzedClass() const noexcept {
	return this->clazz;
}


} /* namespace alinous */
