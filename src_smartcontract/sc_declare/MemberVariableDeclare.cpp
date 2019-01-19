/*
 * MemberVariableDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare/AccessControlDeclare.h"
#include "sc_declare_types/AbstractType.h"
#include "base/UnicodeString.h"

namespace alinous {

MemberVariableDeclare::MemberVariableDeclare() : CodeElement(CodeElement::MEMBER_VARIABLE_DECLARE) {
	this->ctrl = nullptr;
	this->type = nullptr;
	this->_static = false;
	this->name = nullptr;
}

MemberVariableDeclare::~MemberVariableDeclare() {
	if(this->ctrl){
		delete this->ctrl;
	}
	if(this->type){
		delete this->type;
	}
	if(this->name){
		delete this->name;
	}
}

void MemberVariableDeclare::setAccessControl(AccessControlDeclare* ctrl) noexcept {
	this->ctrl = ctrl;
}

void MemberVariableDeclare::setType(AbstractType* type) noexcept {
	this->type = type;
}

void MemberVariableDeclare::setStatic(bool s) noexcept {
	this->_static = s;
}

void MemberVariableDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

} /* namespace alinous */
