/*
 * FunctionArguments.cpp
 *
 *  Created on: 2019/11/03
 *      Author: iizuka
 */

#include "vm/variable_access/FunctionArguments.h"
#include "instance/instance_ref/AbstractReference.h"
#include "instance/IAbstractVmInstanceSubstance.h"

namespace alinous {

FunctionArguments::FunctionArguments() {
	this->returnedValue = nullptr;
	this->_this = nullptr;
}

FunctionArguments::~FunctionArguments() {

}

void FunctionArguments::addSubstance(IAbstractVmInstanceSubstance* ref) noexcept {
	this->list.addElement(ref);
}

void FunctionArguments::setThisPtr(VmClassInstance* _this) noexcept {
	this->_this = _this;
}

VmClassInstance* FunctionArguments::getThisPtr() const noexcept {
	return this->_this;
}

const ArrayList<IAbstractVmInstanceSubstance>* FunctionArguments::getArguments() const noexcept {
	return &this->list;
}

AbstractVmInstance* alinous::FunctionArguments::getReturnedValue() const noexcept {
	return this->returnedValue;
}

void alinous::FunctionArguments::setReturnedValue(AbstractVmInstance* inst) noexcept {
	this->returnedValue = inst;
}


} /* namespace alinous */
