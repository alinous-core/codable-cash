/*
 * DomType.cpp
 *
 *  Created on: 2020/06/26
 *      Author: iizuka
 */

#include "lang/sc_declare_types/DomType.h"

#include "base/UnicodeString.h"

namespace alinous {

const UnicodeString DomType::TYPE_NAME(L"var");

DomType::DomType() : AbstractType(CodeElement::TYPE_DOM) {

}

DomType::~DomType() {

}

int DomType::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractType::binarySize();

	return total;
}

void DomType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_DOM);
	AbstractType::toBinary(out);
}

void DomType::fromBinary(ByteBuffer* in) {
	AbstractType::fromBinary(in);
}

const UnicodeString* DomType::toString() noexcept {
	return &TYPE_NAME;
}

} /* namespace alinous */
