/*
 * ByteType.cpp
 *
 *  Created on: 2019/05/24
 *      Author: iizuka
 */

#include "sc_declare_types/ByteType.h"

#include "base/UnicodeString.h"

namespace alinous {

const UnicodeString ByteType::TYPE_NAME(L"byte");

ByteType::ByteType() : AbstractPrimitiveType(CodeElement::TYPE_BYTE) {
}

ByteType::~ByteType() {
}

int ByteType::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void ByteType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_BYTE);
}

void ByteType::fromBinary(ByteBuffer* in) {
}

const UnicodeString* ByteType::toString() noexcept {
	return &TYPE_NAME;
}

} /* namespace alinous */
