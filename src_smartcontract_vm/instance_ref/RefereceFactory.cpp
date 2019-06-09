/*
 * RefereceFactory.cpp
 *
 *  Created on: 2019/06/09
 *      Author: iizuka
 */

#include "instance_ref/RefereceFactory.h"
#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare_types/AbstractType.h"

namespace alinous {

AbstractReference* RefereceFactory::createReferenceFromDefinition(MemberVariableDeclare* dec) {
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
		break;
	case CodeElement::TYPE_LONG:
		break;
	default:
		break;
	}

	return ref;
}

} /* namespace alinous */

