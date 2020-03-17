/*
 * AbstractReservedClassDeclare.cpp
 *
 *  Created on: 2020/03/17
 *      Author: iizuka
 */

#include "reserved_classes/AbstractReservedClassDeclare.h"

#include "sc_declare/MethodDeclare.h"
#include "sc_declare/MemberVariableDeclare.h"

#include "base/ArrayList.h"


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

ArrayList<MethodDeclare>* AbstractReservedClassDeclare::getMethods() noexcept {
	return this->methods;
}

ArrayList<MemberVariableDeclare>* AbstractReservedClassDeclare::getMemberVariables() noexcept {
	return this->members;
}

} /* namespace alinous */
