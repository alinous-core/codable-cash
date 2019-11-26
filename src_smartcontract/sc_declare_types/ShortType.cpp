/*
 * ShortType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/ShortType.h"

#include "base/UnicodeString.h"

namespace alinous {

const UnicodeString ShortType::TYPE_NAME(L"short");

ShortType::ShortType() : AbstractPrimitiveType(CodeElement::TYPE_SHORT) {
}

ShortType::~ShortType() {
}

int ShortType::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void ShortType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_SHORT);
}

void ShortType::fromBinary(ByteBuffer* in) {
}

const UnicodeString* ShortType::toString() noexcept {
	return &TYPE_NAME;
}


} /* namespace alinous */
