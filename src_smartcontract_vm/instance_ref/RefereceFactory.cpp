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

		break;
	case CodeElement::TYPE_CHAR:
		break;
	case CodeElement::TYPE_SHORT:
		break;
	case CodeElement::TYPE_INT:
		ref = PrimitiveReference::createIntReference(vm, 0);
		break;
	case CodeElement::TYPE_LONG:
		break;
	case CodeElement::TYPE_OBJECT:
		break;
	default:
		break;
	}

	return ref;
}

} /* namespace alinous */

