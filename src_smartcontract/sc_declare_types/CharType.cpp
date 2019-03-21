/*
 * CharType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/CharType.h"

namespace alinous {

CharType::CharType() : AbstractPrimitiveType(CodeElement::TYPE_CHAR) {
}

CharType::~CharType() {
}

int CharType::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void CharType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_CHAR);
}

void CharType::fromBinary(ByteBuffer* in) {
}


} /* namespace alinous */
