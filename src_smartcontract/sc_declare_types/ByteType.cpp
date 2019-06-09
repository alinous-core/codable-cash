/*
 * ByteType.cpp
 *
 *  Created on: 2019/05/24
 *      Author: iizuka
 */

#include "sc_declare_types/ByteType.h"

namespace alinous {

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

} /* namespace alinous */
