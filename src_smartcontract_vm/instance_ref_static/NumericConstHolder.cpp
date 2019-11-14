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
	GcManager* gc = vm->getGc();

	gc->addRefReference(rootRef, referene);
	map->put(key, referene);

	return referene;
}


} /* namespace alinous */
