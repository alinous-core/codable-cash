/*
 * ClassDeclareBlock.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc_declare/ClassDeclareBlock.h"
#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare/MethodDeclare.h"

namespace alinous {

ClassDeclareBlock::ClassDeclareBlock()  : CodeElement(CodeElement::CLASS_DECLARE_BLOCK) {
}

ClassDeclareBlock::~ClassDeclareBlock() {
	this->methods.deleteElements();
	this->variables.deleteElements();
}

void ClassDeclareBlock::addMethod(MethodDeclare* method) noexcept {
	this->methods.addElement(method);
}

void ClassDeclareBlock::addVariable(MemberVariableDeclare* variable) noexcept {
	this->variables.addElement(variable);
}

} /* namespace alinous */

int alinous::ClassDeclareBlock::binarySize() const {
}

void alinous::ClassDeclareBlock::toBinary(ByteBuffer* out) {
}

void alinous::ClassDeclareBlock::fromBinary(ByteBuffer* in) {
}
