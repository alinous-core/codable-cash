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

VmStringInstance* StringConstHolder::newStringConstInstance(const UnicodeString* str, VirtualMachine* vm) {
	VmStringInstance* inst = this->stringVariables.get(str);

	if(inst == nullptr){
		inst = new(vm) VmStringInstance(vm, str);

		this->stringVariables.put(str, inst);
	}

	return inst;
}

void StringConstHolder::removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept {
	GcManager* gc = vm->getGc();

	Iterator<UnicodeString>* it = this->stringVariables.keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		VmStringInstance* inst = this->stringVariables.get(key);

		gc->removeInstanceReference(rootRef, inst);
	}

}

} /* namespace alinous */
