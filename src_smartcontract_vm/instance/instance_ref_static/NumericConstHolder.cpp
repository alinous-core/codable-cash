/*
 * NumericConstHolder.cpp
 *
 *  Created on: 2019/11/14
 *      Author: iizuka
 */

#include "instance/instance_ref_static/NumericConstHolder.h"

#include "instance/instance_ref/PrimitiveReference.h"
#include "instance/instance_ref/RefereceFactory.h"
#include "instance/instance_ref/VmRootReference.h"
#include "instance/instance_ref/ConstStaticPrimitive.h"

#include "instance/instance_gc/GcManager.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "base/StackRelease.h"


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

	referene = makeConstStaticPrimitive(value, type, vm);

	map->put(key, referene);

	return referene;
}

ConstStaticPrimitive* NumericConstHolder::makeConstStaticPrimitive(int64_t value, uint8_t type, VirtualMachine* vm) {
	PrimitiveReference* referene = RefereceFactory::createNumericReference(value, type, vm); __STP(referene);

	return new(vm) ConstStaticPrimitive(referene);
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
