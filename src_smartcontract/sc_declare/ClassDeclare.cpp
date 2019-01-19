/*
 * ClassDeclare.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/ClassDeclareBlock.h"
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
}

void ClassDeclare::setBlock(ClassDeclareBlock* block) noexcept {
	this->block = block;
}

void alinous::ClassDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

} /* namespace alinous */
