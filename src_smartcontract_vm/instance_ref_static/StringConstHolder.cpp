/*
 * StringConstHolder.cpp
 *
 *  Created on: 2020/03/18
 *      Author: iizuka
 */

#include "instance_ref_static/StringConstHolder.h"

#include "instance_ref/VmRootReference.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "instance_string/VmStringInstance.h"

#include "instance_gc/GcManager.h"


namespace alinous {

StringConstHolder::StringConstHolder() {

}

StringConstHolder::~StringConstHolder() {

}

VmStringInstance* StringConstHolder::newStringConstInstance(VmRootReference* rootRef, const UnicodeString* str, VirtualMachine* vm) {
	AbstractReference* ref = this->stringVariables.get(str);

	if(ref == nullptr){
		VmStringInstance* inst = new(vm) VmStringInstance(vm, str);
		AbstractReference* ref = inst->wrap(rootRef, vm);

		this->stringVariables.put(str, ref);
	}

	return dynamic_cast<VmStringInstance*>(ref->getInstance());
}

void StringConstHolder::removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept {
	GcManager* gc = vm->getGc();

	Iterator<UnicodeString>* it = this->stringVariables.keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		AbstractReference* ref = this->stringVariables.get(key);

		gc->registerObject(ref);
		delete ref;
	}

}

} /* namespace alinous */
