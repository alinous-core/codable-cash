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

int alinous::ArgumentDeclare::binarySize() const {
	checkNotNull(this->type);
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += this->type->binarySize();
	total += stringSize(this->name);

	return total;
}

void alinous::ArgumentDeclare::toBinary(ByteBuffer* out) {
	checkNotNull(this->type);
	checkNotNull(this->name);

	out->putShort(CodeElement::ARGUMENT_DECLARE);
	this->type->toBinary(out);
	putString(out, this->name);
}

void alinous::ArgumentDeclare::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsType(element);
	this->type = dynamic_cast<AbstractType*>(element);

	this->name = getString(in);
}

} /* namespace alinous */
