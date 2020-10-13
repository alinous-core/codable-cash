/*
 * RefereceFactory.cpp
 *
 *  Created on: 2019/06/09
 *      Author: iizuka
 */

#include "instance/instance_ref/RefereceFactory.h"
#include "lang/sc_declare/MemberVariableDeclare.h"
#include "lang/sc_declare_types/AbstractType.h"

#include "instance/VmInstanceTypesConst.h"

#include "vm/VirtualMachine.h"
#include "instance/instance_ref/PrimitiveReference.h"
#include "instance/instance_ref/ObjectReference.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_array/ArrayReference.h"

#include "instance/instance_dom/DomRuntimeReference.h"

namespace alinous {

AbstractReference* RefereceFactory::createReferenceFromDefinition(IAbstractVmInstanceSubstance* owner, MemberVariableDeclare* dec, VirtualMachine* vm) {
	AbstractType* type = dec->getType();

	// array
	int dim = type->getDimension();
	if(dim > 0){
		return new(vm) ArrayReference(owner, vm);
	}

	short kind = type->getKind();
	AbstractReference* ref = nullptr;

	switch(kind){
	case CodeElement::TYPE_BOOL:
		ref = PrimitiveReference::createBoolReference(vm, 0);
		break;
	case CodeElement::TYPE_BYTE:
		ref = PrimitiveReference::createByteReference(vm, 0);
		break;
	case CodeElement::TYPE_CHAR:
		ref = PrimitiveReference::createCharReference(vm, 0);
		break;
	case CodeElement::TYPE_SHORT:
		ref = PrimitiveReference::createShortReference(vm, 0);
		break;
	case CodeElement::TYPE_INT:
		ref = PrimitiveReference::createIntReference(vm, 0);
		break;
	case CodeElement::TYPE_LONG:
		ref = PrimitiveReference::createLongReference(vm, 0);
		break;
	case AnalyzedType::TYPE_DOM:
		ref = new(vm) DomRuntimeReference(owner, vm);
		break;
	case CodeElement::TYPE_OBJECT:
	case CodeElement::TYPE_STRING:
	default:
		ref = createObjectReferenceFromDefinition(owner, dec, vm);
		break;
	}

	return ref;
}

AbstractReference* RefereceFactory::createObjectReferenceFromDefinition(IAbstractVmInstanceSubstance* owner, MemberVariableDeclare* dec, VirtualMachine* vm) {
	AnalyzedType at = dec->getAnalyzedType();

	uint8_t type = at.getType();

	ObjectReference* ref = nullptr;
	if(type == AnalyzedType::TYPE_STRING){
		ref = new(vm) ObjectReference(owner, VmInstanceTypesConst::REF_OBJ, ObjectReference::STRING_INSTANCE);
	}else{
		ref = new(vm) ObjectReference(owner, VmInstanceTypesConst::REF_OBJ, ObjectReference::CLASS_INSTANCE);
	}

	return ref;
}

AbstractReference* RefereceFactory::createReferenceFromAnalyzedType(IAbstractVmInstanceSubstance* owner, const AnalyzedType* atype, VirtualMachine* vm) {
	AbstractReference* ref = nullptr;

	// is Array
	if(atype->isArray()){
		return createArrayReferenceFromAnalyzedType(owner, atype, vm);
	}

	uint8_t type = atype->getType();
	switch(type){
	case AnalyzedType::TYPE_BOOL:
		ref = PrimitiveReference::createBoolReference(vm, 0);
		break;
	case AnalyzedType::TYPE_BYTE:
		ref = PrimitiveReference::createByteReference(vm, 0);
		break;
	case AnalyzedType::TYPE_CHAR:
		ref = PrimitiveReference::createCharReference(vm, 0);
		break;
	case AnalyzedType::TYPE_SHORT:
		ref = PrimitiveReference::createShortReference(vm, 0);
		break;
	case AnalyzedType::TYPE_INT:
		ref = PrimitiveReference::createIntReference(vm, 0);
		break;
	case AnalyzedType::TYPE_LONG:
		ref = PrimitiveReference::createLongReference(vm, 0);
		break;
	case AnalyzedType::TYPE_STRING:
		ref = new(vm) ObjectReference(owner, VmInstanceTypesConst::REF_OBJ, ObjectReference::STRING_INSTANCE);
		break;
	case AnalyzedType::TYPE_DOM:
		ref = new(vm) DomRuntimeReference(owner, vm);
		break;
	case AnalyzedType::TYPE_OBJECT:
	default:
		ref = new(vm) ObjectReference(owner, VmInstanceTypesConst::REF_OBJ, ObjectReference::CLASS_INSTANCE);
		break;
	}

	return ref;
}

AbstractReference* RefereceFactory::createArrayReferenceFromAnalyzedType(IAbstractVmInstanceSubstance* owner, const AnalyzedType* atype, VirtualMachine* vm) {
	ArrayReference* ref = new(vm) ArrayReference(owner, vm);

	return ref;
}

/***
 * type is analyzed type
 */
PrimitiveReference* RefereceFactory::createNumericReference(int64_t value, uint8_t type, VirtualMachine* vm) {
	PrimitiveReference* ref = nullptr;
	switch(type){
	case AnalyzedType::TYPE_LONG:
		ref = PrimitiveReference::createLongReference(vm, value);
		break;
	case AnalyzedType::TYPE_INT:
	default:
		ref = PrimitiveReference::createIntReference(vm, value);
		break;
	}

	return ref;
}


} /* namespace alinous */
