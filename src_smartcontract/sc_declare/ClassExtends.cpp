/*
 * ClassExtends.cpp
 *
 *  Created on: 2019/06/19
 *      Author: iizuka
 */

#include "sc_declare/ClassExtends.h"
#include "sc_declare/ClassName.h"

namespace alinous {

ClassExtends::ClassExtends() : CodeElement(CodeElement::CLASS_EXTENDS) {
	this->className = nullptr;
}

ClassExtends::~ClassExtends() {
	delete this->className;
}

void ClassExtends::setClassName(ClassName* className) noexcept {
	this->className = className;
}

int ClassExtends::binarySize() const {
	checkNotNull(this->className);

	int total = sizeof(uint16_t);
	total += this->className->binarySize();

	return total;
}

void ClassExtends::toBinary(ByteBuffer* out) {
	checkNotNull(this->className);

	out->putShort(CodeElement::CLASS_EXTENDS);
	this->className->toBinary(out);
}

void ClassExtends::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::CLASS_NAME);

	this->className = dynamic_cast<ClassName*>(element);
}

} /* namespace alinous */
