/*
 * NumericArgument.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "ext_arguments/NumericArgument.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_ref/PrimitiveReference.h"


namespace alinous {

NumericArgument::NumericArgument(int64_t value, uint8_t atype) {
	this->data = value;
	this->atype = new AnalyzedType(atype);
}

NumericArgument::~NumericArgument() {
	delete this->atype;
}

AnalyzedType NumericArgument::getType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* NumericArgument::interpret(VirtualMachine* vm) {
	uint8_t type = this->atype->getType();

	PrimitiveReference* ref = nullptr;

	switch(type){
	case AnalyzedType::TYPE_BYTE:
		ref = PrimitiveReference::createByteReference(vm, this->data);
		break;
	case AnalyzedType::TYPE_CHAR:
		ref = PrimitiveReference::createCharReference(vm, this->data);
		break;
	case AnalyzedType::TYPE_SHORT:
		ref = PrimitiveReference::createShortReference(vm, this->data);
		break;
	case AnalyzedType::TYPE_LONG:
		ref = PrimitiveReference::createLongReference(vm, this->data);
		break;
	case AnalyzedType::TYPE_INT:
	default:
		ref = PrimitiveReference::createIntReference(vm, this->data);
		break;
	}

	return ref;
}

} /* namespace alinous */
