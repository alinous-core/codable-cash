/*
 * VoidType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "lang/sc_declare_types/VoidType.h"

#include "base/UnicodeString.h"


namespace alinous {

const UnicodeString VoidType::TYPE_NAME(L"void");

VoidType::VoidType() : AbstractType(CodeElement::TYPE_VOID) {

}

VoidType::~VoidType() {
}

int VoidType::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void VoidType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_VOID);
}

void VoidType::fromBinary(ByteBuffer* in) {
}

const UnicodeString* VoidType::toString() noexcept {
	return &TYPE_NAME;
}


} /* namespace alinous */
