/*
 * ClassTypeReference.cpp
 *
 *  Created on: 2020/04/29
 *      Author: iizuka
 */

#include "instance_ref_class_static/ClassTypeReference.h"

#include "instance/VmInstanceTypesConst.h"
#include "instance/IAbstractVmInstanceSubstance.h"

#include "vm/VirtualMachine.h"

#include "sc_analyze/AnalyzedType.h"


namespace alinous {

ClassTypeReference::ClassTypeReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm, const AnalyzedType* type)
	: AbstractReference(owner, VmInstanceTypesConst::REF_CLASS_TYPE) {
	this->atype = new AnalyzedType(*type);

}

ClassTypeReference::~ClassTypeReference() {
	delete this->atype;
}

IAbstractVmInstanceSubstance* ClassTypeReference::getInstance() noexcept {
	return nullptr;
}

} /* namespace alinous */
