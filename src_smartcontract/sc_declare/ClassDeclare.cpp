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

int ClassDeclare::binarySize() const {
	checkNotNull(this->block);
	checkNotNull(this->name);

	int total = sizeof(uint16_t);

	total += stringSize(this->name);
	total += this->block->binarySize();

	return total;
}

void ClassDeclare::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);
	checkNotNull(this->block);

	out->putShort(CodeElement::CLASS_DECLARE);

	putString(out, this->name);
	this->block->toBinary(out);
}

void ClassDeclare::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	CodeElement* element = CodeElement::createFromBinary(in);
	checkKind(element, CodeElement::CLASS_DECLARE_BLOCK);
	this->block = dynamic_cast<ClassDeclareBlock*>(element);
}

} /* namespace alinous */
