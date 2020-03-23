/*
 * NumericConstHolder.cpp
 *
 *  Created on: 2019/11/14
 *      Author: iizuka
 */

#include "instance_ref_static/NumericConstHolder.h"

#include "instance_ref/PrimitiveReference.h"
#include "instance_ref/RefereceFactory.h"
#include "instance_ref/VmRootReference.h"

#include "instance_gc/GcManager.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"


namespace alinous {

NumericConstHolder::NumericConstHolder() {
}

NumericConstHolder::~NumericConstHolder() {

}

PrimitiveReference* NumericConstHolder::newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm) {
	PrimitiveReference* referene = nullptr;
	HashMap<LongIntegerKey, PrimitiveReference>* map = &this->intVariables;

	if(type == AnalyzedType::TYPE_LONG){
		map = &this->longVariables;
	}

	LongIntegerKey key(value);
	referene = map->get(&key);
	if(referene != nullptr){
		return referene;
	}

	referene = RefereceFactory::createNumericReference(value, type, vm);
	VmRootReference* rootRef = vm->getVmRootReference();

	map->put(key, referene);

	return referene;
}

void NumericConstHolder::removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept {
	Iterator<LongIntegerKey>* it = this->intVariables.keySet()->iterator();
	while(it->hasNext()){
		const LongIntegerKey* key = it->next();
		PrimitiveReference* ref = this->intVariables.get(key);

		delete ref;
	}
	delete it;

	it = this->longVariables.keySet()->iterator();
	while(it->hasNext()){
		const LongIntegerKey* key = it->next();
		PrimitiveReference* ref = this->longVariables.get(key);

		delete ref;
	}
	delete it;
}


} /* namespace alinous */
