/*
 * RefereceFactory.cpp
 *
 *  Created on: 2019/06/09
 *      Author: iizuka
 */

#include "instance_ref/RefereceFactory.h"
#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare_types/AbstractType.h"

#include "vm/VirtualMachine.h"
#include "instance_ref/PrimitiveReference.h"
#include "instance_ref/ObjectReference.h"

#include "sc_analyze/AnalyzedType.h"

namespace alinous {

AbstractReference* RefereceFactory::createReferenceFromDefinition(MemberVariableDeclare* dec, VirtualMachine* vm) {
	AbstractType* type = dec->getType();

	short kind = type->getKind();
	AbstractReference* ref = nullptr;

	switch(kind){
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
	case CodeElement::TYPE_OBJECT:
	default:
		ref = createObjectReferenceFromDefinition(dec, vm);
		break;
	}

	return ref;
}

AbstractReference* RefereceFactory::createObjectReferenceFromDefinition(MemberVariableDeclare* dec, VirtualMachine* vm) {
	ObjectReference* ref = new(vm) ObjectReference(AbstractReference::REF_OBJ);

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
