/*
 * ByteType.cpp
 *
 *  Created on: 2019/05/24
 *      Author: iizuka
 */

#include "lang/sc_declare_types/ByteType.h"

#include "base/UnicodeString.h"

namespace alinous {

const UnicodeString ByteType::TYPE_NAME(L"byte");

ByteType::ByteType() : AbstractPrimitiveType(CodeElement::TYPE_BYTE) {
}

ByteType::~ByteType() {
}

int ByteType::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractType::binarySize();

	return total;
}

void ByteType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_BYTE);
	AbstractType::toBinary(out);
}

void ByteType::fromBinary(ByteBuffer* in) {
	AbstractType::fromBinary(in);
}

const UnicodeString* ByteType::toString() noexcept {
	return &TYPE_NAME;
}

} /* namespace alinous */
