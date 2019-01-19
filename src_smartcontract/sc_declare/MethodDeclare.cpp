/*
 * MethodDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "sc_declare/MethodDeclare.h"
#include "base/UnicodeString.h"

namespace alinous {

MethodDeclare::MethodDeclare() : CodeElement(CodeElement::METHOD_DECLARE) {
	this->_static = false;
	this->name = nullptr;
}

MethodDeclare::~MethodDeclare() {
	if(this->name){
		delete this->name;
	}

}

void MethodDeclare::setStatic(bool s) noexcept {
	this->_static = s;
}

void MethodDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

} /* namespace alinous */
