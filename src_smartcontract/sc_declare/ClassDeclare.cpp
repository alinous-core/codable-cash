/*
 * ClassDeclare.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/ClassDeclareBlock.h"
#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare/MethodDeclare.h"
#include "base/UnicodeString.h"

namespace alinous {

ClassDeclare::ClassDeclare() : CodeElement(CodeElement::CLASS_DECLARE) {
	this->block = nullptr;
	this->name = nullptr;
}

ClassDeclare::~ClassDeclare() {
	if(this->block != nullptr){
		delete this->block;
	}
	if(this->name != nullptr){
		delete this->name;
	}
	this->methods.deleteElements();
	this->variables.deleteElements();
}

void ClassDeclare::setBlock(ClassDeclareBlock* block) noexcept {
	this->block = block;
}

void alinous::ClassDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void ClassDeclare::addMethod(MethodDeclare* method) noexcept {
	this->methods.addElement(method);
}

void ClassDeclare::addVariable(MemberVariableDeclare* variable) noexcept {
	this->variables.addElement(variable);
}

} /* namespace alinous */
