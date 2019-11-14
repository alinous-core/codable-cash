/*
 * StaticInstanceHolder.cpp
 *
 *  Created on: 2019/11/14
 *      Author: iizuka
 */

#include "instance_ref_static/StaticInstanceHolder.h"

#include "instance_ref_static/NumericConstHolder.h"

namespace alinous {

StaticInstanceHolder::StaticInstanceHolder() {
	this->numeric = new NumericConstHolder();
}

StaticInstanceHolder::~StaticInstanceHolder() {
	delete this->numeric;
}

PrimitiveReference* StaticInstanceHolder::newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm) {
	return this->numeric->newNumericConstReferenece(value, type, vm);
}


} /* namespace alinous */
