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

int ClassDeclareBlock::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->variables.size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* val = this->variables.get(i);
		total += val->binarySize();
	}

	total += sizeof(uint32_t);
	maxLoop = this->methods.size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods.get(i);
		total += method->binarySize();
	}

	return total;
}

void ClassDeclareBlock::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::CLASS_DECLARE_BLOCK);

	uint32_t maxLoop = this->variables.size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* val = this->variables.get(i);
		val->toBinary(out);
	}

	maxLoop = this->methods.size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods.get(i);
		method->toBinary(out);
	}
}

void ClassDeclareBlock::fromBinary(ByteBuffer* in) {
	uint32_t maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::MEMBER_VARIABLE_DECLARE);

		MemberVariableDeclare* val = dynamic_cast<MemberVariableDeclare*>(element);
		this->variables.addElement(val);
	}

	maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::METHOD_DECLARE);

		MethodDeclare* method = dynamic_cast<MethodDeclare*>(element);
		this->methods.addElement(method);
	}
}


} /* namespace alinous */
