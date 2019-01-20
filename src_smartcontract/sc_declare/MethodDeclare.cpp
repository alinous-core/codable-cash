/*
 * MethodDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "sc_declare/MethodDeclare.h"
#include "sc_declare/AccessControlDeclare.h"
#include "sc_declare/ArgumentsListDeclare.h"
#include "sc_declare_types/AbstractType.h"
#include "sc_statement/StatementBlock.h"
#include "base/UnicodeString.h"

namespace alinous {

MethodDeclare::MethodDeclare() : CodeElement(CodeElement::METHOD_DECLARE) {
	this->_static = false;
	this->name = nullptr;
	this->ctrl = nullptr;
	this->type = nullptr;
	this->args = nullptr;
	this->block = nullptr;
}

MethodDeclare::~MethodDeclare() {
	if(this->name){
		delete this->name;
	}
	if(this->ctrl){
		delete this->ctrl;
	}
	if(this->type){
		delete this->type;
	}
	if(this->args){
		delete this->args;
	}
	if(this->block){
		delete this->block;
	}
}

void MethodDeclare::setStatic(bool s) noexcept {
	this->_static = s;
}

void MethodDeclare::setAccessControl(AccessControlDeclare* ctrl) noexcept {
	this->ctrl = ctrl;
}

void MethodDeclare::setType(AbstractType* type) noexcept {
	this->type = type;
}

void MethodDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void MethodDeclare::setArguments(ArgumentsListDeclare* args) noexcept {
	this->args = args;
}

void MethodDeclare::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

} /* namespace alinous */
