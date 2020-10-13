/*
 * StringConstHolder.cpp
 *
 *  Created on: 2020/03/18
 *      Author: iizuka
 */

#include "instance/instance_ref_static/StringConstHolder.h"

#include "instance/instance_ref/VmRootReference.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "instance/instance_string/VmStringInstance.h"

#include "instance/instance_gc/GcManager.h"


namespace alinous {

StringConstHolder::StringConstHolder() {

}

StringConstHolder::~StringConstHolder() {

}

VmStringInstance* StringConstHolder::newStringConstInstance(VmRootReference* rootRef, const UnicodeString* str, VirtualMachine* vm) {
	AbstractReference* ref = this->stringVariables.get(str);

	if(ref == nullptr){
		GcManager* gc = vm->getGc();

		VmStringInstance* inst = new(vm) VmStringInstance(vm, str);
		ref = inst->wrap(rootRef, vm);
		gc->registerObject(ref);

		this->stringVariables.put(str, ref);
	}

	IAbstractVmInstanceSubstance* substance = ref->getInstance();

	return dynamic_cast<VmStringInstance*>(substance);
}

void StringConstHolder::removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept {
	GcManager* gc = vm->getGc();

	Iterator<UnicodeString>* it = this->stringVariables.keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		AbstractReference* ref = this->stringVariables.get(key);

		gc->removeObject(ref);
		delete ref;
	}

}

} /* namespace alinous */
