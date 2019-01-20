/*
 * ArgumentDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "sc_declare/ArgumentDeclare.h"
#include "sc_declare_types/AbstractType.h"
#include "base/UnicodeString.h"

namespace alinous {

ArgumentDeclare::ArgumentDeclare() : CodeElement(CodeElement::ARGUMENT_DECLARE) {
	this->type = nullptr;
	this->name = nullptr;
}

ArgumentDeclare::~ArgumentDeclare() {
	if(this->type){
		delete this->type;
	}
	if(this->name){
		delete this->name;
	}
}

void ArgumentDeclare::setType(AbstractType* type) noexcept {
	this->type = type;
}

void ArgumentDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}


} /* namespace alinous */

