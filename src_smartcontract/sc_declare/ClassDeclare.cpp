/*
 * ClassDeclare.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/ClassDeclareBlock.h"

namespace alinous {

ClassDeclare::ClassDeclare() : CodeElement(CodeElement::CLASS_DECLARE) {
	this->block = nullptr;
}

ClassDeclare::~ClassDeclare() {
	if(this->block != nullptr){
		delete this->block;
	}
}

void ClassDeclare::setBlock(ClassDeclareBlock* block) {
	this->block = block;
}

} /* namespace alinous */
