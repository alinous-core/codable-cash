/*
 * CharType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "lang/sc_declare_types/CharType.h"

#include "base/UnicodeString.h"

namespace alinous {

const UnicodeString CharType::TYPE_NAME(L"char");

CharType::CharType() : AbstractPrimitiveType(CodeElement::TYPE_CHAR) {
}

CharType::~CharType() {
}

int CharType::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractType::binarySize();

	return total;
}

void CharType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_CHAR);
	AbstractType::toBinary(out);
}

void CharType::fromBinary(ByteBuffer* in) {
	AbstractType::fromBinary(in);
}

const UnicodeString* CharType::toString() noexcept {
	return &TYPE_NAME;
}


} /* namespace alinous */
