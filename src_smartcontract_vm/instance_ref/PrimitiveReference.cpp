/*
 * PrimitiveReference.cpp
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#include "instance_ref/PrimitiveReference.h"

namespace alinous {

PrimitiveReference::PrimitiveReference(uint8_t type) : AbstractReference(type) {

}

PrimitiveReference::~PrimitiveReference() {

}

PrimitiveReference* PrimitiveReference::createIntReference(VirtualMachine* vm) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(AbstractVmInstance::REF_INT);

	return ref;
}

} /* namespace alinous */
