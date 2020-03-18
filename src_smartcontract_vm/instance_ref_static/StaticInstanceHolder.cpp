/*
 * StaticInstanceHolder.cpp
 *
 *  Created on: 2019/11/14
 *      Author: iizuka
 */

#include "instance_ref_static/StaticInstanceHolder.h"

#include "instance_ref_static/NumericConstHolder.h"
#include "instance_ref_static/StringConstHolder.h"


namespace alinous {

StaticInstanceHolder::StaticInstanceHolder() { // @suppress("Class members should be properly initialized")
	this->numeric = new NumericConstHolder();
	this->stringConsts = new StringConstHolder();
}

StaticInstanceHolder::~StaticInstanceHolder() {
	delete this->numeric;
	delete this->stringConsts;
}

PrimitiveReference* StaticInstanceHolder::newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm) {
	return this->numeric->newNumericConstReferenece(value, type, vm);
}

VmStringInstance* StaticInstanceHolder::newStringConstInstance(const UnicodeString* str, VirtualMachine* vm) {
	return this->stringConsts->newStringConstInstance(str, vm);
}

void StaticInstanceHolder::removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept {
	this->numeric->removeInnerReferences(rootRef, vm);
	this->stringConsts->removeInnerReferences(rootRef, vm);

}

} /* namespace alinous */
