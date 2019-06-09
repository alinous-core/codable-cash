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
		// FIXME object referenec
		break;
	default:
		break;
	}

	return ref;
}

} /* namespace alinous */

