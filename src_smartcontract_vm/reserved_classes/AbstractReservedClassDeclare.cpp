/*
 * AbstractReservedClassDeclare.cpp
 *
 *  Created on: 2020/03/17
 *      Author: iizuka
 */

#include "reserved_classes/AbstractReservedClassDeclare.h"

namespace alinous {

AbstractReservedClassDeclare::AbstractReservedClassDeclare() : ClassDeclare() {
	this->methods = new ArrayList<MethodDeclare>();
	this->members = new ArrayList<MemberVariableDeclare>();
}

AbstractReservedClassDeclare::~AbstractReservedClassDeclare() {
	this->methods->deleteElements();
	delete this->methods;

	this->members->deleteElements();
	delete this->members;
}

} /* namespace alinous */
